import java.util.*;
import java.io.*;

public class Solution {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		String[] names = new String[n];
		for(int i = 0; i < n; i++) {
			names[i] = in.readLine();
		}
		int index = 0;
		for(int i = 0; i < m; i++) {
			int s = Integer.parseInt(in.readLine());
			index += s;
			index %= n;
			System.out.println(names[index]);
			index++;
		}
	}
}