import java.util.ArrayList;

class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {

        ArrayList<ArrayList<Integer>> arr = new ArrayList<>(numCourses);

        for (int i = 0; i < numCourses; i++) {
            arr.add(new ArrayList<>());
        }


        for(int i=0; i< prerequisites.length; i++) {
            arr.get(prerequisites[i][1]).add( prerequisites[i][0]);
        }

        return cycleDetect( numCourses,prerequisites , arr);
    }

    private boolean cycleDetect(int numCourses , int[][] prerequisites, ArrayList<ArrayList<Integer>> arr) {

        int[] visited = new int[numCourses];

        for(int i=0; i< numCourses; i++) {
            if(visited[i] == 0) {
                if ( dfs(i , visited , arr) ) {
                    return false;
                }
            }

        }

        return true;

    }

    private boolean dfs(int i, int[] visited , ArrayList<ArrayList<Integer>> arr) {

        visited[i] = 1;

        for(int j = 0; j< arr.get(i).size() ; j++) {
            if( visited[ arr.get(i).get(j)] == 0) {
                if (dfs(arr.get(i).get(j) , visited , arr) == true ) {
                    return true;
                }
            }

            else if( visited[arr.get(i).get(j)] == 1) {
                return true;
            }

            else if( visited[arr.get(i).get(j)] == 2) {
                continue;
            }
        }

        visited[i] = 2;

        return false;

    }
}