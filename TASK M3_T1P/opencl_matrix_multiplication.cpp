#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <CL/cl.hpp>

using namespace std;
using namespace std::chrono;

const int N = 1000; // MATRIX SIZE
const int work_group_size = 16; // WORK GROUP SIZE

int main()
{
    // OpenCL Initialization
    cl::Context context(CL_DEVICE_TYPE_GPU);
    vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Program::Sources sources;
    ifstream kernel_file("matrix_mult_kernel.cl");
    string kernel_code((istreambuf_iterator<char>(kernel_file)), istreambuf_iterator<char>());
    sources.push_back({kernel_code.c_str(), kernel_code.length()});

    cl::Program program(context, sources);
    program.build(devices);

    cl::CommandQueue queue(context, devices[0]);

    cl::Kernel kernel(program, "matrix_mult");

    // VARIABLES A & B INITIALIZED
    vector<int> A(N*N), B(N*N), C(N*N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    for (int i = 0; i < N*N; i++) {
        A[i] = dis(gen);
        B[i] = dis(gen);
    }

    // BUFFERS CREATED AND COPIED TO DEVICE
    cl::Buffer buffer_A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*N*N, A.data());
    cl::Buffer buffer_B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*N*N, B.data());
    cl::Buffer buffer_C(context, CL_MEM_WRITE_ONLY, sizeof(int)*N*N);

    // KERNEL CONFIGURED
    kernel.setArg(0, buffer_A);
    kernel.setArg(1, buffer_B);
    kernel.setArg(2, buffer_C);
    kernel.setArg(3, N);
    kernel.setArg(4, work_group_size);

    // CALCULATION OF C
    auto start_time = high_resolution_clock::now(); // START TIME CALCULATION

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(N, N), cl::NDRange(work_group_size, work_group_size));

    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*N*N, C.data());

    auto end_time = high_resolution_clock::now(); // END TIME CALCULATION

    // OUTPUT FILE GENERATED
    ofstream fout("output.txt");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fout << C[i*N+j] << " ";
        }
        fout << endl;
    }

    // CALCULATION OF EXECUTION TIME
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " milliseconds." << endl;

    return 0;
}
