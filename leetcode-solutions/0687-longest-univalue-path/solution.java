/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    private int ans = 0;

    public int longestUnivaluePath(TreeNode root) {
        dfs(root);
        return ans;
    }

    private int dfs(TreeNode node) {
        if (node == null) return 0;

        int leftLen = dfs(node.left);
        int rightLen = dfs(node.right);

        int leftPath = 0, rightPath = 0;
        if (node.left != null && node.left.val == node.val) {
            leftPath = leftLen + 1;
        }
        if (node.right != null && node.right.val == node.val) {
            rightPath = rightLen + 1;
        }

        ans = Math.max(ans, leftPath + rightPath);
        return Math.max(leftPath, rightPath);
    }
}

