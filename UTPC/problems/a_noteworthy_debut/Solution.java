import java.util.*;
import java.io.*;

public class Solution {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int inputs = Integer.parseInt(in.readLine());
		while(inputs-->0) {
			int n = Integer.parseInt(in.readLine());
			StringTokenizer st = new StringTokenizer(in.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++)
				nums[i] = Integer.parseInt(st.nextToken());
			
			long count = 0;
			for(int i = 0; i < n; i++) {
				long sum = nums[i];
				int left = i;
				while(left > 0 && nums[left-1]+sum<2*nums[i]) {
					left--;
					sum += nums[left];
				}
				int right = i;
				for(int l = left; l <= i; l++) {
					while(right < n-1 && nums[right+1]+sum<2*nums[i]) {
						right++;
						sum += nums[right];
					}
					count += right-i+1;
					sum -= nums[l];
				}
			}
			System.out.println(count);
		}
	}
}