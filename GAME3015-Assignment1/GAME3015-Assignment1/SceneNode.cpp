#include "SceneNode.h"
#include "Game.h"
#include "Command.h"

SceneNode::SceneNode(Game* game)
	: mChildren()
	, mParent(nullptr)
	, game(game)
{
	mWorldPosition = XMFLOAT3(0, 0, 0);
	mWorldScaling = XMFLOAT3(1, 1, 1);
	mWorldRotation = XMFLOAT3(0, 0, 0);
}

/// <summary>
/// Add a child to this node
/// </summary>
/// <param name="child"></param>
void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

/// <summary>
/// Detaches a child from this node
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

/// <summary>
/// calls the update function of this node and its children
/// </summary>
/// <param name="gt"></param>
void SceneNode::update(const GameTimer& gt)
{
	updateCurrent(gt);
	updateChildren(gt);
}

void SceneNode::updateCurrent(const GameTimer& gt)
{
}

void SceneNode::updateChildren(const GameTimer& gt)
{
	for (Ptr& child : mChildren)
	{
		child->update(gt);
	}
}

/// <summary>
/// calls the draw function of this node and its children
/// </summary>
void SceneNode::draw() const
{
	drawCurrent();
	drawChildren();
}

void SceneNode::drawCurrent() const
{
}

void SceneNode::drawChildren() const
{
	for (const Ptr& child : mChildren)
	{
		child->draw();
	}
}

/// <summary>
/// Calls the build function of this node and its children
/// </summary>
void SceneNode::build()
{
	buildCurrent();
	buildChildren();
}

void SceneNode::buildCurrent()
{
}

/// <summary>
/// Calls the build function of this node's children
/// </summary>
void SceneNode::buildChildren()
{
	for (const Ptr& child : mChildren)
	{
		child->build();
	}
}

/// <summary>
/// Returns the world position of this node
/// </summary>
/// <returns></returns>
XMFLOAT3 SceneNode::getWorldPosition() const
{
	return mWorldPosition;
}

/// <summary>
/// Set the position
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void SceneNode::setPosition(float x, float y, float z)
{
	mWorldPosition = XMFLOAT3(x, y, z);
}

/// <summary>
/// Returns the world rotation of this node
/// </summary>
/// <returns></returns>
XMFLOAT3 SceneNode::getWorldRotation() const
{
	return mWorldRotation;
}

/// <summary>
/// set the world rotation of this node
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void SceneNode::setWorldRotation(float x, float y, float z)
{
	mWorldRotation = XMFLOAT3(x, y, z);
}

/// <summary>
/// Scale function
/// </summary>
/// <returns></returns>
XMFLOAT3 SceneNode::getWorldScale() const
{
	return mWorldScaling;
}

/// <summary>
/// setting the Scale function
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void SceneNode::setScale(float x, float y, float z)
{
	mWorldScaling = XMFLOAT3(x, y, z);
}

/// <summary>
/// Returns the world transform of this node
/// </summary>
/// <returns></returns>
XMFLOAT4X4 SceneNode::getWorldTransform() const
{
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T = XMLoadFloat4x4(&transform);

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		XMMATRIX Tp = XMLoadFloat4x4(&node->getTransform());
		T = Tp * T;
	}
	XMStoreFloat4x4(&transform, T);

	return transform;
}

XMFLOAT4X4 SceneNode::getTransform() const
{
	XMFLOAT4X4 transform;
	XMStoreFloat4x4(&transform, XMMatrixScaling(mWorldScaling.x, mWorldScaling.y, mWorldScaling.z) *
		XMMatrixRotationX(mWorldRotation.x) *
		XMMatrixRotationY(mWorldRotation.y) *
		XMMatrixRotationZ(mWorldRotation.z) *
		XMMatrixTranslation(mWorldPosition.x, mWorldPosition.y, mWorldPosition.z));
	return transform;
}

void SceneNode::onCommand(const Command& command, const GameTimer& gt)
{
	if (command.category & getCategory())
		command.action(*this, gt);

	for (Ptr& child : mChildren)
		child->onCommand(command, gt);
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::move(float x, float y, float z)
{
	mWorldPosition.x += x;
	mWorldPosition.y += y;
	mWorldPosition.z += z;
}
