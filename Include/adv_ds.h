//
// Created by angel on 9/09/24.
//


/*
 * @author: Angel Castillo @date: 09/09/2024
 *
 * Here are some of the advanced data structures that you could use in a project:
 *
 * - Graphs
 * - Trees
 * - Ordered and unordered maps
 * - Ordered and unordered sets
 * - Self-balancing trees
 *
 */

#ifndef MYCODEBASE_ADV_DS_H
#define MYCODEBASE_ADV_DS_H

#include "ds.h"

/*
 * @author: Angel Castillo @date 10/09/2024
 *
 * NOTE: Is recommended to use a tmp pointer to a node ...

 */

#define MoveLeft( Node ) ((Node) != NULL ? (Node) = ((Node)->prev) : 0)
#define MoveRigth( Node ) ((Node) != NULL ? (Node) = ((Node)->next) : 0)
#define GetData( Node, type ) ((Node) != NULL ? (type)((Node)->data) : NULL)

/*
 * @author: Angel Castillo @date: 10/09/2024
 *
 *
 *
 */

#define BUCKET( type1, type2 ) \
    typedef struct bucket_##type1##_##type2 { \
      type1 key; \
      type2 value; \
    } bucket_##type1##_##type2;  \
                               \
    NODE(bucket_##type1##_##type2) \
    DLL_INIT(bucket_##type1##_##type2) \

#define B_NODE_TREE(type) typedef Node##type TreeNode##type;

#define LoadNode( Arena, Node ) InitNodeList##type( (Arena), (Node) );

#define B_TREE(type) \
    B_NODE_TREE(type)                 \
    typedef struct Tree##type { \
        Arena* pool; \
        TreeNode##type* root; \
        TreeNode##type* tmp; \
        uint128 height; \
    } Tree##type;    \
                     \
    static inline Tree##type* InitTree##type ( type data ) { \
        Tree##type* tree = safe_malloc( sizeof(Tree##type) );\
        tree->pool = CreateArena( 10*sizeof( NodeTree##type ) ); \
        tree->root = LoadNode( tree->pool, data );   \
        tree->root->data = data; \
        tree->tmp = tree->root;       \
        tree->height = 1; \
    }

#define InOrder( Tree, type ) \
    TreeNode##type* tmp = ((Tree)->root); \
    MoveLeft(tmp); \
    printf("%p");             \
    tmp = ((Tree)->root); \
    MoveLeft(tmp->right); \


#endif //MYCODEBASE_ADV_DS_H
