import java.util.*;
public class remDup
{
        public int removeDuplicates(int[] nums)
        {
                int a = 1;
                int b = 1;
                int c = nums[0];
                for (; a < nums.length; ++a)
                {
                        if (c != nums[a])
                        {
                                c = nums[b] = nums[a];
                                ++b;
                        }
                }
                return b;
        }
        public static void main(String[] args)
        {
                int[] test1 = {0,0,1,1,1,2,2,3,3,4};
                int[] result1 = removeDuplicates(test1);
                for (int ii = 0; ii < result1.length; ++ii)
                {
                        System.out.print(result1[ii] + " ");
                }
        }
}
