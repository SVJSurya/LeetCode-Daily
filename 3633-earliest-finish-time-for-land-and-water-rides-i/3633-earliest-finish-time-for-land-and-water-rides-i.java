class Solution {
    private int cFT(int[] ls, int[] ld, int[] ws, int[] wd) {
        int mini = Integer.MAX_VALUE;

        for(int i=0;i<ls.length;i++) {
            mini = Math.min(mini, ls[i] + ld[i]);
        }

        int ans = Integer.MAX_VALUE;

        for(int i=0;i<ws.length;i++) {
            ans = Math.min(ans, Math.max(mini, ws[i]) + wd[i]);
        }

        return ans;
    }
    public int earliestFinishTime(int[]lST, int[] lD, int[] wST, int[] wD) {
        return Math.min(cFT(lST,lD,wST,wD), cFT(wST,wD,lST,lD));
    }
}