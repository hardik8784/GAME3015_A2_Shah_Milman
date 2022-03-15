/**
* @brief Game class
* Extends DSDApp class. Initilizing the DirectX3D
* 
*/
#pragma once
#include "World.h"
enum class RenderLayer : int
{
    Opaque = 0,
    AlphaTested,
    Count
};
class Game : public D3DApp
{
public:
    /**
    * @brief Game Constructor
    * @param hInstance
    */
    Game(HINSTANCE hInstance);
    /**
    * @brief  Game Constructor
    * @param rhs constant referance of game class
    */
    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;
    /**
    * @brief Game class destructor
    */
    ~Game();
    /**
    * @brief Initialize function
    */
    virtual bool Initialize()override;

private:
    /**
   * @brief Resize function
   */
    virtual void OnResize()override;
    /**
   * @brief Update function
   * @param GameTimer 
   */
    virtual void Update(const GameTimer& gt)override;
    /*
    * @brief Draw function
    */
    virtual void Draw(const GameTimer& gt)override;
    /*
    * @brief OnMouseDown
    * @param btnState button state, (int x, int y) coordinates of the mouse
    */
    virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
    /*
   * @brief OnMouseUp
   * @param btnState button state, (int x, int y) coordinates of the mouse
   */
    virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
    /*
   * @brief OnMouseMove
   * @param btnState button state, (int x, int y) coordinates of the mouse
   */
    virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

    void OnKeyboardInput(const GameTimer& gt);
    void UpdateCamera(const GameTimer& gt);
    void AnimateMaterials(const GameTimer& gt);
    void UpdateObjectCBs(const GameTimer& gt);
    void UpdateMaterialCBs(const GameTimer& gt);
    void UpdateMainPassCB(const GameTimer& gt);
    /// <summary>
    /// @brief loadTexures
    /// </summary>
    void LoadTextures();
    void BuildRootSignature();
    void BuildDescriptorHeaps();
    void BuildShadersAndInputLayout();
    void BuildShapeGeometry();
    void BuildPSOs();
    void BuildFrameResources();
    /// <summary>
    /// @brief Build materials
    /// </summary>
    void BuildMaterials();
    void BuildRenderItems();
    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

    std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:

    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    UINT mCbvSrvDescriptorSize = 0;

    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

    ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
    std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
    std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    // List of all the render items.
    std::vector<std::unique_ptr<RenderItem>> mAllRitems;

    // Render items divided by PSO.
    std::vector<RenderItem*> mOpaqueRitems;


    std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];
    PassConstants mMainPassCB;



    POINT mLastMousePos;
    Camera mCamera;
    World mWorld;

public:
    /// <summary>
    /// @brief getRenderItems
    /// </summary>
    /// <returns>vector of pointers to render itmes</returns>
    std::vector<std::unique_ptr<RenderItem>>& getRenderItems();
    /// <summary>
    /// @brief getMaterials
    /// </summary>
    /// <returns>map of name of materials and the materials</returns>
    std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials();
    /// <summary>
    /// getGeometries
    /// </summary>
    /// <returns>map containing name of geometries and geometries</returns>
    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries();

};
