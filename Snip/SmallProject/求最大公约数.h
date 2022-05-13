// 确定该算法运行时间的最重要方法是如下定理：　
//if M > N, M mod N < M/2;
//定理不难证明，分为N<=M/2 和 N > M/2两种情况讨论即可。
//该定理告诉我们，求Ｇｃｄ程序在经过两次迭代后，余数最多是原始值的一半。　所以迭代次数至多是：２logN = O ( logN )

unsigned int
gcd( unsigned int M, unsigned int N)
{
    unsigned int Rem;

    while( N > 0 )//M,N大小关系无影响， 因为若N比M大，迭代后两者的值会交换。
    {
        Rem= M% N;
        M= N;
        N= Rem;
    }

    return M;
}