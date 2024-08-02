#include "tree.h"

#include "lvgl/lvgl.h"
#include "lvgl/src/core/lv_obj.h"
#include "lvgl/src/core/lv_obj_pos.h"
#include "lvgl/src/misc/lv_area.h"
#include "lvgl/src/widgets/label/lv_label.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



void init_node(TreeNode *node){
  node->value = 0;
  node->left = NULL;
  node->right = NULL;
}

TreeNode* create_node(Value val){
  TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
  node->value = val;
  node->left = node->right = NULL;
  return node;
}

TreeNode* complete_tree(Value arr[],TreeNode *root,int i,int size){
  if(i < size){
    TreeNode *t= create_node(arr[i]);
    root = t;
    root->left = complete_tree(arr,root->left, 2 * i + 1, size);
    root->right = complete_tree(arr, root->right, 2 * i + 2, size);
  }
  return root;
}

void free_tree(TreeNode *root){
  if (root == NULL){
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
  free(root);
  root = NULL;
}

lv_obj_t* lv_create_node(TreeNode *node,lv_obj_t *parent){
  lv_obj_t *child = lv_obj_create(parent);
  lv_obj_t *label = lv_label_create(child);
  lv_label_set_text(label,"6");
  lv_obj_set_size(child, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  return child;
}
void inorder_traversal(TreeNode *root){
  if (root == NULL){
    return;
  }
  inorder_traversal(root->left);
  printf("%d \n",root->value);
  inorder_traversal(root->right);
}

void render_preorder(TreeNode *root,lv_obj_t *parent,lv_align_t align){
  if (root == NULL){
    return;
  }

  lv_obj_t *lv_node  =  lv_create_node(root,parent);
  lv_obj_align(lv_node, align, 0, 0);
  render_preorder(root->left,lv_node,LV_ALIGN_BOTTOM_LEFT);
  render_preorder(root->right,lv_node,LV_ALIGN_BOTTOM_RIGHT);
}


void render_tree(TreeNode *root){
  lv_obj_t *wrapper = lv_obj_create(lv_screen_active());
  lv_obj_align(wrapper,LV_ALIGN_CENTER,0,0);
  render_preorder(root, wrapper,LV_ALIGN_TOP_MID);
}

void show_tree(){
  Value arr[3] = {2,3,1};
  int size = sizeof(arr)/sizeof(arr[0]);
  TreeNode *root = complete_tree(arr, root, 0, size);
  render_tree(root);
}

