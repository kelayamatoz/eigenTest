#include "Eigen/Dense"
#include <iostream>

struct timespec GetClock()
{
  struct timespec tv;
  clock_gettime(CLOCK_REALTIME,&tv);
  return tv;
}

double GetCurrentTime()
{
  static timespec tv_init=GetClock();

  timespec tv=GetClock();
  return (double)(tv.tv_sec-tv_init.tv_sec)+(double)(tv.tv_nsec-tv_init.tv_nsec)*1e-9;
}

void TestVectorVectorProduct(int N,int num_cycles)
{
  Eigen::VectorXf x=Eigen::VectorXf::Random(N);
  Eigen::VectorXf y=Eigen::VectorXf::Random(N);

  volatile float result=0;//volatile prevents compiling out this code
  for(int i=0;i<num_cycles;i++)
  {
    result+=x.transpose()*y;
  }
}

void TestMatrixVectorProduct(int N,int M,int num_cycles)
{
  Eigen::MatrixXf A=Eigen::MatrixXf::Random(N,M);
  Eigen::VectorXf x=Eigen::VectorXf::Random(M);
  Eigen::VectorXf b=Eigen::VectorXf::Random(N);

  for(int i=0;i<num_cycles;i++)
  {
    b+=A*x;
  }
}

void TestMatrixMatrixProduct(int N,int L,int M,int num_cycles)
{
  Eigen::MatrixXf A=Eigen::MatrixXf::Random(N,L);
  Eigen::MatrixXf B=Eigen::MatrixXf::Random(L,M);
  Eigen::MatrixXf C=Eigen::MatrixXf::Random(N,M);

  for(int i=0;i<num_cycles;i++)
  {
    C+=A*B;
  }
}

int main(int argc,char** argv)
{
  int num_cycles=1000;
  if(argc>=2)
    num_cycles=atoi(argv[1]);

  //Eigen::MatrixXf A=Eigen::MatrixXf::Random(1000,1000);
  //Eigen::VectorXf x=Eigen::VectorXf::Random(1000);

  {
    double time_start=GetCurrentTime();
    TestVectorVectorProduct(128,num_cycles);
    double total_time=GetCurrentTime()-time_start;
    std::cout << "VectorVectorProduct total=" << total_time << " average=" << total_time/num_cycles << std::endl;;
  }

  {
    double time_start=GetCurrentTime();
    TestMatrixVectorProduct(128,128,num_cycles);
    double total_time=GetCurrentTime()-time_start;
    std::cout << "MatrixVectorProduct total=" << total_time << " average=" << total_time/num_cycles << std::endl;;
  }

  {
    double time_start=GetCurrentTime();
    TestMatrixMatrixProduct(128,128,128,num_cycles);
    double total_time=GetCurrentTime()-time_start;
    std::cout << "MatrixMatrixProduct total=" << total_time << " average=" << total_time/num_cycles << std::endl;;
  }

  return 0;
}
