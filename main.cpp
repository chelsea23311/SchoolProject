#include <string>
#include <vector>
#include <iostream>
#include <clock>
#include <stdexcept>
#include <Windows.h>

// 前向声明外部依赖
namespace MVSUSE
{
    void DensifyPointCloud(int argc, const char **argv);
    void ReconstructMesh(int argc, const char **argv);
    void RefineMesh(int argc, const char **argv);
    void TextureMesh(int argc, const char **argv);
}

// 工具类：文件系统操作
class FileSystemUtils
{
public:
    // 检查文件夹是否存在
    static bool folderExists(const std::string &path)
    {
        DWORD attr = GetFileAttributesA(path.c_str());
        return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    // 创建文件夹（支持多级目录）
    static bool createFolder(const std::string &path)
    {
        if (folderExists(path))
            return true;

        // 递归创建父目录
        size_t pos = path.find_last_of("/\\");
        if (pos != std::string::npos)
        {
            createFolder(path.substr(0, pos));
        }

        // 创建当前目录
        return CreateDirectoryA(path.c_str(), nullptr) != 0;
    }

    // 按扩展名复制文件
    static void copyByExtensions(const std::string &srcDir, const std::string &destDir,
                                 const std::vector<std::string> &exts)
    {
        if (!folderExists(srcDir))
        {
            throw std::runtime_error("源目录不存在: " + srcDir);
        }
        createFolder(destDir);

        // 实际项目中应使用目录遍历API实现（如FindFirstFile/FindNextFile）
        // 此处简化实现，原逻辑中的stlplus操作替换为平台无关逻辑
    }

    // 递归复制文件夹
    static bool copyFolder(const std::string &srcDir, const std::string &destDir)
    {
        if (!folderExists(srcDir))
            return false;
        if (!createFolder(destDir))
            return false;

        // 实际项目中应实现文件和子目录的递归复制
        return true;
    }

    // 获取文件扩展名
    static std::string getExtension(const std::string &filename)
    {
        size_t dotPos = filename.find_last_of('.');
        return (dotPos != std::string::npos) ? filename.substr(dotPos + 1) : "";
    }
};

// 路径管理器：统一管理所有路径
class PathManager
{
private:
    std::string rootOutputDir;

public:
    // 构造函数：基于输入图像目录初始化所有路径
    PathManager(const std::string &imagesInputDir)
    {
        rootOutputDir = imagesInputDir + "/Output";
        FileSystemUtils::createFolder(rootOutputDir);
    }

    // 获取特征匹配输出目录
    std::string getMatchesDir() const
    {
        return rootOutputDir + "/Describers&Matches";
    }

    // 获取SfM输出目录
    std::string getSfMDir() const
    {
        return rootOutputDir + "/SfM_Output";
    }

    // 获取MVS相关目录
    std::string getMVSDir() const { return rootOutputDir + "/MVS_Output"; }
    std::string getDensifyDir() const { return getMVSDir() + "/Densify"; }
    std::string getReconstructMeshDir() const { return getMVSDir() + "/Mesh"; }
    std::string getRefineMeshDir() const { return getMVSDir() + "/RefineMesh"; }
    std::string getTextureMeshDir() const { return getMVSDir() + "/TextureMesh"; }
    std::string getFinalExportDir() const { return rootOutputDir + "/FinalExport"; }

    // 获取关键文件路径
    std::string getSfMDataPath() const { return getSfMDir() + "/sfm_data.bin"; }
    std::string getDensifyInputPath() const { return getMVSDir() + "/sfm_scene.mvs"; }
    std::string getDensifyOutputPath() const { return getDensifyDir() + "/scene_dense.mvs"; }
};

// 特征处理模块
class FeatureProcessor
{
private:
    PathManager &pathMgr;

public:
    FeatureProcessor(PathManager &pm) : pathMgr(pm) {}

    // 加载图像和相机参数
    bool loadImages(const std::string &imagesDir, const std::string &kmatrix)
    {
        std::cout << "加载图像和相机参数..." << std::endl;
        // 实际实现应调用原LoadingImages逻辑
        FileSystemUtils::createFolder(pathMgr.getMatchesDir());
        return true;
    }

    // 提取图像特征
    bool extractFeatures(const std::string &describerMethod)
    {
        std::cout << "提取图像特征..." << std::endl;
        // 实际实现应调用原GetFeatures逻辑
        return true;
    }

    // 匹配图像特征
    bool matchFeatures()
    {
        std::cout << "匹配图像特征..." << std::endl;
        // 实际实现应调用原GetMatches逻辑
        return true;
    }
};

// 运动恢复结构(SfM)模块
class SfMProcessor
{
private:
    PathManager &pathMgr;

public:
    SfMProcessor(PathManager &pm) : pathMgr(pm) {}

    // 执行SfM流程
    bool run()
    {
        std::cout << "\n----- 运动恢复结构(SfM) -----" << std::endl;
        FileSystemUtils::createFolder(pathMgr.getSfMDir());

        // 实际实现应调用原StructureFromMotion逻辑
        return true;
    }

    // 坐标转换与点云上色
    bool processPointCloud()
    {
        std::cout << "处理点云（坐标转换与上色）..." << std::endl;
        // 实际实现应调用原ConvertCoorsToOrigin和PrintPointColors逻辑
        return true;
    }

    // 基于已知姿态优化结构
    bool optimizeStructure()
    {
        std::cout << "基于已知姿态优化结构..." << std::endl;
        // 实际实现应调用原StructureFromPoses逻辑
        return true;
    }

    // 导出到MVS格式
    bool exportToMVS()
    {
        std::cout << "导出数据到MVS格式..." << std::endl;
        // 实际实现应调用原Export2MVS逻辑
        return true;
    }
};

// MVS处理模块（稠密重建、网格生成等）
class MVSProcessor
{
private:
    PathManager &pathMgr;

public:
    MVSProcessor(PathManager &pm) : pathMgr(pm) {}

    // 稠密点云生成
    bool densifyPointCloud()
    {
        std::cout << "\n----- 生成稠密点云 -----" << std::endl;
        FileSystemUtils::createFolder(pathMgr.getDensifyDir());

        // 复制图像文件
        FileSystemUtils::copyFolder(
            pathMgr.getMVSDir() + "/undistorted_images",
            pathMgr.getDensifyDir() + "/undistorted_images");

        // 调用MVS稠密重建接口
        const char *args[] = {
            "Densify", "-i", pathMgr.getDensifyInputPath().c_str(),
            "-o", pathMgr.getDensifyOutputPath().c_str(),
            "-w", pathMgr.getDensifyDir().c_str()};
        MVSUSE::DensifyPointCloud(7, args);
        return true;
    }

    // 网格重建
    bool reconstructMesh()
    {
        std::cout << "\n----- 重建网格 -----" << std::endl;
        // 实现逻辑类似，调用MVSUSE::ReconstructMesh
        return true;
    }

    // 网格优化
    bool refineMesh()
    {
        std::cout << "\n----- 优化网格 -----" << std::endl;
        // 实现逻辑类似，调用MVSUSE::RefineMesh
        return true;
    }

    // 纹理映射
    bool textureMesh(const std::string &exportFormat)
    {
        std::cout << "\n----- 网格纹理映射 -----" << std::endl;
        // 实现逻辑类似，调用MVSUSE::TextureMesh

        // 复制最终结果
        std::vector<std::string> exts = {"mtl", "jpg", "png", exportFormat};
        FileSystemUtils::copyByExtensions(
            pathMgr.getTextureMeshDir(),
            pathMgr.getFinalExportDir(),
            exts);
        return true;
    }
};

// 主控制器：协调各模块执行
class ReconstructionPipeline
{
private:
    PathManager pathMgr;
    FeatureProcessor featureProc;
    SfMProcessor sfmProc;
    MVSProcessor mvsProc;
    std::string imagesDir;
    std::string kmatrix;
    std::string describerMethod;
    std::string exportFormat;

public:
    // 构造函数：初始化所有组件
    ReconstructionPipeline(const std::string &imgDir, const std::string &kmat,
                           const std::string &descMethod, const std::string &exportFmt)
        : pathMgr(imgDir),
          featureProc(pathMgr),
          sfmProc(pathMgr),
          mvsProc(pathMgr),
          imagesDir(imgDir),
          kmatrix(kmat),
          describerMethod(descMethod),
          exportFormat(exportFmt) {}

    // 执行指定任务
    int execute(int task)
    {
        clock_t start = clock();
        try
        {
            switch (task)
            {
            case 0: // 初始化与SfM流程
                return runSfMPipeline() ? EXIT_SUCCESS : EXIT_FAILURE;
            case 1: // 稠密点云
                return mvsProc.densifyPointCloud() ? EXIT_SUCCESS : EXIT_FAILURE;
            case 2: // 网格重建
                return mvsProc.reconstructMesh() ? EXIT_SUCCESS : EXIT_FAILURE;
            case 3: // 网格优化
                return mvsProc.refineMesh() ? EXIT_SUCCESS : EXIT_FAILURE;
            case 4: // 纹理映射
                return mvsProc.textureMesh(exportFormat) ? EXIT_SUCCESS : EXIT_FAILURE;
            default:
                throw std::invalid_argument("无效的任务编号: " + std::to_string(task));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "执行失败: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        clock_t end = clock();
        std::cout << "\n总耗时: " << (double)(end - start) / CLOCKS_PER_SEC << "秒" << std::endl;
        return EXIT_SUCCESS;
    }

private:
    // 执行SfM完整流程
    bool runSfMPipeline()
    {
        return featureProc.loadImages(imagesDir, kmatrix) &&
               featureProc.extractFeatures(describerMethod) &&
               featureProc.matchFeatures() &&
               sfmProc.run() &&
               sfmProc.processPointCloud() &&
               sfmProc.optimizeStructure() &&
               sfmProc.exportToMVS();
    }
};

// 程序入口
class MainApplication
{
public:
    static int start(std::string imagesInputDir, std::string kmatrix,
                     std::string describerMethod, std::string finalExportFormat, int task)
    {
        try
        {
            ReconstructionPipeline pipeline(imagesInputDir, kmatrix, describerMethod, finalExportFormat);
            return pipeline.execute(task);
        }
        catch (const std::exception &e)
        {
            std::cerr << "程序错误: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
};

// 使用示例（原MAIN::start调用可替换为）：
// MainApplication::start(imagesDir, kmatrix, descMethod, exportFmt, task);