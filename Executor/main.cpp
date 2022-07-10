
#include <string>
#include <any>

#include "AttributeConfig.h"
#include "Context.h"
#include "Node.h"
#include "EvaluationContext.h"


#define CONTEXT_FLAG "-context"
#define CONTEXT_SHORT_FLAG "-ctx"

#define NODE_FLAG "-node"
#define NODE_SHORT_FLAG "-n"

#define LOG_FLAG "-logFile"
#define LOG_FLAG_SHORT "-lf"



void EvaluateNodes(std::vector<NodeLibrary::Node*> nodes)
{
    for (NodeLibrary::Node* node : nodes)
    {
        NodeLibrary::EvaluationContext ctx(node);
        ctx.Evaluate(true);
    }
}


int main(int argc, char *argv[])
{
    NodeLibrary::Context::Initialize();

    for(int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg == CONTEXT_FLAG || arg == CONTEXT_SHORT_FLAG)
        {
            std::string contextFile(argv[i+1]);
            NodeLibrary::Context::DeserializeFromFile(contextFile);
        }
    }


    std::string logFile;
    std::vector<NodeLibrary::Node*> nodes;
    for(int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg == NODE_FLAG || arg == NODE_SHORT_FLAG)
        {
            NodeLibrary::Node* node = NodeLibrary::Context::FindNode(std::string(argv[i+1]));
            if (!node)
            {
                continue;
            }

            nodes.push_back(node);
            continue;
        }

        if (arg == LOG_FLAG || arg == LOG_FLAG_SHORT)
        {
            logFile = std::string(argv[i+1]);
            continue;
        }
    }

    if (nodes.empty())
    {
        return 0;
    }

    EvaluateNodes(nodes);
    return 0;
}
