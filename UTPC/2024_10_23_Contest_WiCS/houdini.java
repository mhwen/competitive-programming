import java.util.*;
import java.io.*;

public class houdini {
	
	static int ans = 1;
	
	public static int dfs(int curr, int prev, ArrayList<Integer>[] con, int[] v) {
		int tot = v[curr];
		for(int next : con[curr])
			if(next != prev)
				tot+=dfs(next, curr, con, v);
		tot%=2;
		if(tot%2==0 && curr != 0)
			ans++;
		return tot;
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(in.readLine());
		StringTokenizer st = new StringTokenizer(in.readLine());
		int[] v = new int[n];
		ArrayList<Integer>[] con = new ArrayList[n];
		for(int i = 0; i < n; i++) {
			v[i] = Integer.parseInt(st.nextToken())%2;
			con[i] = new ArrayList<>();
		}
		
		for(int i = 0; i < n-1; i++) {
			st = new StringTokenizer(in.readLine());
			int a = Integer.parseInt(st.nextToken())-1;
			int b = Integer.parseInt(st.nextToken())-1;
			con[a].add(b);
			con[b].add(a);
		}
		if(dfs(0, -1, con, v) == 1)
			ans = -1;
		System.out.println(ans);
	}
}