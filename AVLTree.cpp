#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL){}
};

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){} 
}; 

TreeNode* LL_Rotate(TreeNode* p) 
{
	TreeNode* lc = p->left;
	p->left = lc->right ;
	lc->right  = p;
	return lc;
}

TreeNode* RR_Rotate(TreeNode* p)
{
	TreeNode* rc = p->right;
	p->right = rc->left;
	rc->left = p;
	return rc;
}

TreeNode* LR_Rotate(TreeNode* p)
{
	TreeNode* tmp = p->left;
	p->left = RR_Rotate(tmp);
	return LL_Rotate(p);
}

TreeNode* RL_Rotate(TreeNode* p)
{
	TreeNode* tmp = p->right;
	p->right = LL_Rotate(tmp);
	return RR_Rotate(p);
}

int height(TreeNode* p)
{
	if(p == NULL)
		return 0;
	return max(height(p->left), height(p->right) + 1);
}

int diff(TreeNode *p)
{
	return height(p->left) - height(p->right);
}

TreeNode* Balance(TreeNode* p)
{
	int balanceFactor = diff(p);
	if(balanceFactor > 1) // 左子树高于右子树 
	{
		if(diff(p->left) > 0) //左左外侧
			p = LL_Rotate(p); 
		else //左右内侧
			p = LR_Rotate(p); 
	}
	else if(balanceFactor < -1)
	{
		if(diff(p->right) > 0) //右左内侧
			p = RL_Rotate(p);
		else //右右外侧
			p = RR_Rotate(p); 
	}
	return p;
}

TreeNode* insert(TreeNode* p, int val)
{
	if(p == NULL)
	{
		p = new TreeNode(val);
		return p;
	}
	else if(val < p->val)
	{
		
		p->left = insert(p->left, val);
		p = Balance(p);
	}
	else if(val > p->val)
	{
		p->right = insert(p->right, val);
		p = Balance(p);
	}

	return p;
}

TreeNode* sortedListToBST(ListNode* head)
{
	ListNode* p = head;
	TreeNode* tree = NULL;
	while(p != NULL)
	{
		tree = insert(tree, p->val);
		p = p->next;
	}
			
	return tree;
}

void Inorder(TreeNode* root)
{
	if(root == NULL)
		return;
	Inorder(root->left);
	cout << root->val << " ";
	Inorder(root->right);
}

int main()
{
	vector<int> nums = {-9, -5, -3, 0, 3, 5, 6, 9};
	ListNode* head = new ListNode(-10);
	ListNode* rear = head;
	for(int i = 0; i < nums.size(); i ++)
	{
		ListNode* node = new ListNode(nums[i]);
		node->next = rear->next;
		rear->next = node;
	}
	
	TreeNode *bst = sortedListToBST(head);
	Inorder(bst);
	return 0; 
}
