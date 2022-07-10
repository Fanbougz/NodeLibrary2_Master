//
// Created by Dorian on 3/13/2022.
//

#include "mathLibrary.h"
#include "stringLibrary.h"
#include "mayaLibrary.h"
#include "files.h"


#define EXPORT "C" void __declspec(dllexport) __cdecl


extern EXPORT RegisterPlugin(NodeLibrary::PluginNodeLoader* loader)
{
    loader->InitializeContext();

    // Math nodes :
    loader->RegisterNode<MathNodes::ConstantIntBuilder>("ConstantInt");

    loader->RegisterNode<MathNodes::ConstantFloatBuilder>("ConstantFloat");

    loader->RegisterNode<MathNodes::ConstantDoubleBuilder>("ConstantDouble");

    loader->RegisterNode<MathNodes::Add2IntsBuilder>("Add2Ints");

    loader->RegisterNode<MathNodes::Add2FloatsBuilder>("Add2Floats");

    loader->RegisterNode<MathNodes::Add2DoublesBuilder>("Add2Doubles");

    loader->RegisterNode<MathNodes::IntDynamicManualBuilder>("IntDynamicManual");


    // String nodes :
    loader->RegisterNode<StringNodes::ConstantStringBuilder>("ConstantString");

    loader->RegisterNode<StringNodes::StringsJoinBuilder>("StringsJoin");

    loader->RegisterNode<StringNodes::StringSplitBuilder>("StringsSplit");

    // File nodes :
    loader->RegisterNode<FileNodes::SaveToPyhonFileBuilder>("SaveToPythonFile");

    // Maya nodes :
    loader->RegisterNode<MayaNodes::MayaOpenSceneCommandBuilder>("MayaOpenScene");

    loader->RegisterNode<MayaNodes::MayaRenameSceneCommandBuilder>("MayaRenameScene");

    loader->RegisterNode<MayaNodes::MayaCreateNodeCommandBuilder>("MayaCreateNode");

    loader->RegisterNode<MayaNodes::MayaSaveSceneCommandBuilder>("MayaSaveScene");

    loader->RegisterNode<MayaNodes::MayapyComposeCommandBuilder>("MayapyComposeCommand");

    loader->RegisterNode<MayaNodes::MayapyLaunchCommandBuilder>("MayapyLaunchCommand");

    loader->RegisterNode<MayaNodes::MayapyExecuteFileBuilder>("MayapyExecuteFile");

}


int main()
{

}