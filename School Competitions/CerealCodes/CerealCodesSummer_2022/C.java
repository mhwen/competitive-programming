import java.util.*;
import java.io.*;

public class Solution {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int inputs = Integer.parseInt(in.readLine());
		while(inputs-->0) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int sum = 0;
			while(n-->0) {
				if(k%6==0) {
					k /= 6;
					sum += 6;
				}
				else if(k%4==0) {
					k /= 4;
					sum += 4;
				}
				else if(k%5==0) {
					k /= 5;
					sum += 5;
				}
				else if(k%3==0) {
					k /= 3;
					sum += 3;
				}
				else if(k%2==0) {
					k /= 2;
					sum += 2;
				}
				else {
					sum += 1;
				}
			}
			if(k > 1) {
				System.out.println(-1);
			}
			else {
				System.out.println(sum);
			}
		}
	}
}