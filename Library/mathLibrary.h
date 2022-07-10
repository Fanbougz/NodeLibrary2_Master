//
// Created by Dorian on 2/22/2022.
//

#include <iostream>
#include <AttributeConfig.h>
#include <Context.h>
#include <Node.h>
#include <Attribute.h>
#include <PluginNodeLoader.h>
#include <NodeFactory.h>
#include <NodeEvaluationContext.h>
#include <libExport.h>


namespace MathNodes
{
    class NodeLibrary2_API ConstantInt: public NodeLibrary::Node
    {
    public:
        ConstantInt(std::string id): NodeLibrary::Node(id)
        {

        }

        std::string Type() const override
        {
            return "ConstantInt";
        }

        void InitAttributes() override
        {
            CreateAttribute<int>("Output", NodeLibrary::Attribute::ValueType::Single,
                                 NodeLibrary::Attribute::Type::Static);
        }
    };


    class NodeLibrary2_API ConstantIntBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new ConstantInt("");
        }
    };


    class NodeLibrary2_API ConstantFloat: public NodeLibrary::Node
    {
    public:
        ConstantFloat(std::string id): NodeLibrary::Node(id)
        {

        }

        std::string Type() const override
        {
            return "ConstantFloat";
        }

        void InitAttributes() override
        {
            CreateAttribute<float>("Output", NodeLibrary::Attribute::ValueType::Single,
                                 NodeLibrary::Attribute::Type::Static);
        }
    };


    class NodeLibrary2_API ConstantFloatBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new ConstantFloat("");
        }
    };


    class NodeLibrary2_API ConstantDouble: public NodeLibrary::Node
    {
    public:
        ConstantDouble(std::string id): NodeLibrary::Node(id)
        {

        }

        std::string Type() const override
        {
            return "ConstantDouble";
        }

        void InitAttributes() override
        {
            CreateAttribute<float>("Output", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Static);
        }
    };


    class NodeLibrary2_API ConstantDoubleBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new ConstantDouble("");
        }
    };


    class NodeLibrary2_API Add2Ints: public NodeLibrary::Node
    {
    public:
        Add2Ints(std::string id): NodeLibrary::Node(id){}

        std::string Type() const override
        {
            return "Add2Ints";
        }

        [[nodiscard]]
        bool IsDynamic() const override
        {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override
        {
            return true;
        }

        void InitAttributes() override
        {
            CreateAttribute<int>("Input1", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<int>("Input2", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<int>("Output", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Output);
       }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            auto input1 = ctx.GetAttributeValue<int>("Input1");
            auto input2 = ctx.GetAttributeValue<int>("Input2");
            return ctx.SetAttributeValue("Output", input1 + input2);
        }
    };


    class NodeLibrary2_API Add2IntsBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new Add2Ints("");
        }
    };


    class NodeLibrary2_API Add2Floats: public NodeLibrary::Node
    {
    public:
        Add2Floats(std::string id) : NodeLibrary::Node(id){}

        std::string Type() const override
        {
            return "Add2Floats";
        }

        [[nodiscard]]
        bool IsDynamic() const override
        {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override
        {
            return true;
        }

        void InitAttributes() override
        {
            CreateAttribute<float>("Input1", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<float>("Input2", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<float>("Output", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            auto input1 = ctx.GetAttributeValue<float>("Input1");
            auto input2 = ctx.GetAttributeValue<float>("Input2");
            return ctx.SetAttributeValue("Output", input1 + input2);
        }
    };


    class NodeLibrary2_API Add2FloatsBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new Add2Floats("");
        }
    };


    class NodeLibrary2_API Add2Doubles: public NodeLibrary::Node
    {
    public:
        Add2Doubles(std::string id): NodeLibrary::Node(id){}

        std::string Type() const override
        {
            return "Add2Doubles";
        }

        [[nodiscard]]
        bool IsDynamic() const override
        {
            return true;
        }

        [[nodiscard]]
        bool AutoComputes() const override
        {
            return true;
        }

        void InitAttributes() override
        {
            CreateAttribute<double>("Input1", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<double>("Input2", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Input);
            CreateAttribute<double>("Output", NodeLibrary::Attribute::ValueType::Single,
                                   NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            auto input1 = ctx.GetAttributeValue<double>("Input1");
            auto input2 = ctx.GetAttributeValue<double>("Input2");
            return ctx.SetAttributeValue("Output", input1 + input2);
        }
    };


    class NodeLibrary2_API Add2DoublesBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new Add2Doubles("");
        }
    };

    class NodeLibrary2_API IntDynamicManual: public NodeLibrary::Node
    {
    public:
        IntDynamicManual(std::string name): NodeLibrary::Node(std::move(name))
        {

        }
        void InitAttributes() override
        {
            CreateAttribute<int>("Input", NodeLibrary::Attribute::ValueType::Single,
                                 NodeLibrary::Attribute::Type::Input, nullptr);
            CreateAttribute<int>("Output", NodeLibrary::Attribute::ValueType::Single,
                                 NodeLibrary::Attribute::Type::Output, nullptr);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            int value = ctx.GetAttributeValue<int>("Input");
            ctx.SetAttributeValue("Output", value);
            return true;
        }
    };


    class IntDynamicManualBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new IntDynamicManual("");
        }
    };
}

