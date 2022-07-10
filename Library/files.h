//
// Created by Dorian on 6/7/2022.
//

#ifndef LIBRARY_FILES_H
#define LIBRARY_FILES_H

#endif //LIBRARY_FILES_H


#include "Context.h"
#include "Node.h"
#include "Attribute.h"
#include "NodeEvaluationContext.h"

#include <boost/filesystem.hpp>

#include <string>
#include <cstdio>


namespace FileNodes {
    class NodeLibrary2_API TemporaryFile : public NodeLibrary::PythonCommandNode {
    public:
        TemporaryFile(std::string id) : NodeLibrary::PythonCommandNode(id) {

        }

        void InitAttributes() override {
            CreateAttribute<std::string>("Extension", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("TemporaryFilePath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override {
            std::string ext = ctx.GetAttributeValue<std::string>("Extension");

            return true;
        }
    };


    class NodeLibrary2_API SaveToPythonFile : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "SaveToPythonFile";
        }

        SaveToPythonFile(std::string id) : NodeLibrary::Node(id)
        {

        }

        bool IsDynamic() const override
        {
            return true;
        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("Directory", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Filename", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<bool>("UseTemporaryFilename", NodeLibrary::Attribute::ValueType::Single,
                                  NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Content", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("OutputFilepath", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext &ctx) override
        {
            auto directory = ctx.GetAttributeValue<std::string>("Directory");
            auto filename = ctx.GetAttributeValue<std::string>("Filename");
            auto content = ctx.GetAttributeValue<std::string>("Content");
            bool temp = ctx.GetAttributeValue<bool>("UseTemporaryFilename");

            if (temp)
            {
                filename = boost::filesystem::path(std::tmpnam(nullptr)).filename().string();
            }

            if (directory.empty())
            {
                directory = boost::filesystem::temp_directory_path().string();
            }

            boost::filesystem::path result;
            result.append(directory);
            result.append(filename);

            std::ofstream file;
            file.open(result.string());
            if (!content.empty())
                file << content;

            file.close();
            return ctx.SetAttributeValue("OutputFilepath", result.string());
        }
    };


    class NodeLibrary2_API SaveToPyhonFileBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new SaveToPythonFile("");
        }
    };
}