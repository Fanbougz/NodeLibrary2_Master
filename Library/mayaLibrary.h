//
// Created by Dorian on 6/5/2022.
//

#ifndef LIBRARY_MAYALIBRARY_H
#define LIBRARY_MAYALIBRARY_H

#endif //LIBRARY_MAYALIBRARY_H


#include "libExport.h"
#include "Context.h"
#include "Node.h"
#include "Attribute.h"
#include "NodeEvaluationContext.h"


#include <string>


namespace MayaNodes
{

    class NodeLibrary2_API MayaAction : public NodeLibrary::CompoundNode {
        [[nodiscard]]
        bool IsDynamic() const override {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override {
            return true;
        }

        void InitAttributes() override {
            CreateAttribute<std::string>("MayaFilePath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Static);
        }

        bool PreEvaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            char *mayapyPath = "";

            return true;
        }

        bool PostEvaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            return false;
        }
    };


    class NodeLibrary2_API MayaOpenSceneCommand : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayaOpenScene";
        }

        explicit MayaOpenSceneCommand(std::string id) : NodeLibrary::Node(id)
        {

        }

        [[nodiscard]]
        bool IsDynamic() const override {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override {
            return true;
        }

        void InitAttributes() override {
            CreateAttribute<std::string>("MayaFilePath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Command", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            auto mayapath = ctx.GetAttributeValue<std::string>("MayaFilePath");
            ctx.SetAttributeValue<std::string>("Command", "cmds.file(\"" + mayapath + "\", open=True)");
            return true;
        }
    };


    class NodeLibrary2_API MayaOpenSceneCommandBuilder : public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayaOpenSceneCommand("");
        }
    };


    class NodeLibrary2_API MayaRenameSceneCommand: public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayaRenameScene";
        }

        bool IsDynamic() const override
        {
            return true;
        }

        bool AutoComputes() const override
        {
            return true;
        }

        MayaRenameSceneCommand(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("Filepath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Command", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            std::string path = ctx.GetAttributeValue<std::string>("Filepath");

            std::string cmd = "cmds.file(rename=\"" + path + "\")";
            ctx.SetAttributeValue("Command", cmd);
            return true;
        }
    };


    class NodeLibrary2_API MayaRenameSceneCommandBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayaRenameSceneCommand("");
        }
    };


    class NodeLibrary2_API MayaSaveSceneCommand : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayaSaveScene";
        }

        explicit MayaSaveSceneCommand(std::string id) : NodeLibrary::Node(id)
        {

        }

        [[nodiscard]]
        bool IsDynamic() const override {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override {
            return true;
        }

        void InitAttributes() override {
            CreateAttribute<std::string>("MayaFilePath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Command", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            auto mayapath = ctx.GetAttributeValue<std::string>("MayaFilePath");
            std::string cmd = "if not cmds.file(q=True, sn=True) == \"" + mayapath + "\":\n" +
                              "    cmds.file(rename=\"" + mayapath + "\")\n" +
                              "cmds.file(save=True)";
            ctx.SetAttributeValue<std::string>("Command", cmd);
            return true;
        }
    };


    class NodeLibrary2_API MayaSaveSceneCommandBuilder : public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayaSaveSceneCommand("");
        }
    };


    class NodeLibrary2_API MayaCreateNodeCommand : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayaCreateNode";
        }

        explicit MayaCreateNodeCommand(std::string id) : NodeLibrary::Node(id) {

        }

        [[nodiscard]]
        bool IsDynamic() const override {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override {
            return true;
        }

        void InitAttributes() override {
            CreateAttribute<std::string>("NodeType", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("NodeName", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Command", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            auto nodetype = ctx.GetAttributeValue<std::string>("NodeType");
            auto nodename = ctx.GetAttributeValue<std::string>("NodeName");
            std::string cmd = "cmds.createNode(\"" + nodetype + "\"";
            if (!nodename.empty()) {
                cmd += ", name=\"" + nodename + "\"";
            }
            cmd += ")";
            ctx.SetAttributeValue<std::string>("Command", cmd);
            return true;
        }
    };


    class NodeLibrary2_API MayaCreateNodeCommandBuilder : public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayaCreateNodeCommand("");
        }
    };


    class NodeLibrary2_API MayapyComposeCommand : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayapyComposeCommand";
        }

        explicit MayapyComposeCommand(std::string id) : NodeLibrary::Node(id)
        {

        }

        [[nodiscard]]
        bool IsDynamic() const override {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override {
            return true;
        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("Commands", NodeLibrary::Attribute::ValueType::Multi,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("ResultCommand", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override
        {
            std::string command = "import maya.standalone\nmaya.standalone.initialize(\"python\")\nfrom maya import cmds\n";

            NodeLibrary::Attribute *commandsAttr = GetAttribute("Commands");
            std::vector<std::string> subCommands = commandsAttr->GetArrayValues<std::string>();
            std::cout << "Commands size : " + std::to_string(subCommands.size());
            if (!subCommands.empty())
            {
                for (std::string &subCommand: subCommands)
                {
                    command += "\n" + subCommand;
                }
            }

            ctx.SetAttributeValue("ResultCommand", command);
            return true;
        }
    };


    class NodeLibrary2_API MayapyComposeCommandBuilder : public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayapyComposeCommand("");
        }
    };


    class NodeLibrary2_API MayapyLaunchCommand:public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "MayapyLaunchCommand";
        }

        MayapyLaunchCommand(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("Command", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            std::string command = ctx.GetAttributeValue<std::string>("Command");

            std::string mayapyCmd = "D:\\Programmes\\Autodesk\\Maya\\2023\\Maya2024\\bin\\mayapy.exe -c \"" + command + "\"";
            std::system(mayapyCmd.c_str());
            return true;
        }
    };


    class NodeLibrary2_API MayapyLaunchCommandBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node * CreateNode() override
        {
            return new MayapyLaunchCommand("");
        }
    };


    class NodeLibrary2_API MayapyExecuteFile: public NodeLibrary::Node
    {
        NodeLibrary::Attribute* pythonFile;

    public:
        std::string Type() const override
        {
            return "MayapyExecuteFile";
        }

        MayapyExecuteFile(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            pythonFile = CreateAttribute<std::string>("PythonFile", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            std::string module = ctx.GetAttributeValue<std::string>("PythonFile");
            std::string mayapyCmd = "D:\\Programmes\\Autodesk\\Maya\\2023\\Maya2024\\bin\\mayapy.exe \"" + module + "\"";

            std::system(mayapyCmd.c_str());
            return true;
        }
    };

    class NodeLibrary2_API MayapyExecuteFileBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new MayapyExecuteFile("");
        }
    };
}