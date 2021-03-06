// ObjectListNode.h - manages a list of ObjectNodes
//------------------------------------------------------------------------------
#pragma once

// Includes
//------------------------------------------------------------------------------
#include "Node.h"
#include "Core/Containers/Array.h"

// Forward Declarations
//------------------------------------------------------------------------------
class Args;
class CompilerNode;
class Function;
class NodeGraph;
class ObjectNode;

// ObjectListNode
//------------------------------------------------------------------------------
class ObjectListNode : public Node
{
    REFLECT_NODE_DECLARE( ObjectListNode )
public:
    ObjectListNode();
    virtual bool Initialize( NodeGraph & nodeGraph, const BFFToken * iter, const Function * function ) override;
    virtual ~ObjectListNode() override;

    static inline Node::Type GetTypeS() { return Node::OBJECT_LIST_NODE; }

    virtual bool IsAFile() const override;

    const char * GetObjExtension() const;

    void GetInputFiles( Args & fullArgs, const AString & pre, const AString & post, bool objectsInsteadOfLibs ) const;
    void GetInputFiles( Array< AString > & files ) const;

    CompilerNode * GetCompiler() const;
    CompilerNode * GetPreprocessor() const;

    inline const AString & GetCompilerOptions() const { return m_CompilerOptions; }
    void GetObjectFileName( const AString & fileName, const AString & baseDir, AString & objFile );

    void EnumerateInputFiles( void (*callback)( const AString & inputFile, const AString & baseDir, void * userData ), void * userData ) const;

protected:
    friend class FunctionObjectList;

    virtual bool GatherDynamicDependencies( NodeGraph & nodeGraph, bool forceClean );
    virtual bool DoDynamicDependencies( NodeGraph & nodeGraph, bool forceClean ) override;
    virtual BuildResult DoBuild( Job * job ) override;

    // internal helpers
    bool CreateDynamicObjectNode( NodeGraph & nodeGraph, Node * inputFile, const AString & baseDir, bool isUnityNode = false, bool isIsolatedFromUnityNode = false );
    ObjectNode * CreateObjectNode( NodeGraph & nodeGraph,
                                   const BFFToken * iter,
                                   const Function * function,
                                   const uint32_t flags,
                                   const uint32_t preprocessorFlags,
                                   const AString & compilerOptions,
                                   const AString & compilerOptionsDeoptimized,
                                   const AString & preprocessor,
                                   const AString & preprocessorOptions,
                                   const AString & objectName,
                                   const AString & objectInput,
                                   const AString & pchObjectName );
    ObjectNode * GetPrecompiledHeader() const;

    // Exposed Properties
    AString             m_Compiler;
    AString             m_CompilerOptions;
    AString             m_CompilerOptionsDeoptimized;
    AString             m_CompilerOutputPath;
    AString             m_CompilerOutputPrefix;
    AString             m_CompilerOutputExtension;
    Array< AString >    m_CompilerInputPath;
    Array< AString >    m_CompilerInputPattern;
    Array< AString >    m_CompilerInputExcludePath;
    Array< AString >    m_CompilerInputExcludedFiles;
    Array< AString >    m_CompilerInputExcludePattern;
    Array< AString >    m_CompilerInputFiles;
    Array< AString >    m_CompilerInputUnity;
    AString             m_CompilerInputFilesRoot;
    Array< AString >    m_CompilerInputObjectLists;
    Array< AString >    m_CompilerForceUsing;
    bool                m_CompilerInputAllowNoFiles         = false;
    bool                m_CompilerInputPathRecurse          = true;
    bool                m_CompilerOutputKeepBaseExtension   = false;
    bool                m_DeoptimizeWritableFiles           = false;
    bool                m_DeoptimizeWritableFilesWithToken  = false;
    bool                m_AllowDistribution                 = true;
    bool                m_AllowCaching                      = true;
    AString             m_PCHInputFile;
    AString             m_PCHOutputFile;
    AString             m_PCHOptions;
    AString             m_Preprocessor;
    AString             m_PreprocessorOptions;
    Array< AString >    m_PreBuildDependencyNames;

    // Internal State
    bool                m_UsingPrecompiledHeader            = false;
    AString             m_ExtraPDBPath;
    AString             m_ExtraASMPath;
    uint32_t            m_ObjectListInputStartIndex         = 0;
    uint32_t            m_ObjectListInputEndIndex           = 0;
    uint32_t            m_NumCompilerInputUnity             = 0;
    uint32_t            m_NumCompilerInputFiles             = 0;
    uint32_t            m_NumCompilerInputObjectLists       = 0;
};

//------------------------------------------------------------------------------
