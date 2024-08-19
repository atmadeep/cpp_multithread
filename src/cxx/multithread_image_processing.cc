#include <condition_variable>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>

#if ENABLE_PROFILING
#include <chrono>
#endif

// INFO Conditional compilation for python module
#if BUILD_PYTHON_MODULE
#include <pybind11/pybind11.h>
namespace py = pybind11;
#endif

// INFO queues for consumer producer model.
std::queue<cv::Mat> capture_Queue;
std::queue<cv::Mat> process_Queue;

// INFO mutex locks for queues.
std::mutex capture_Mutex;
std::mutex process_Mutex;

std::condition_variable capture_CondVar;
std::condition_variable process_CondVar;

bool done = false;
int total_frames = 0;

void captureImage() {
  // INFO Open default camera @ id = 0
  cv::VideoCapture cap(0);
  cv::Mat frame;

  // INFO Return error if camera is not opened.
  if (!cap.isOpened()) {
    std::cerr << "Error: Could not open camera." << std::endl;
    done = true;
    return;
  }

  // INFO The camera might send empty frames.
  while (!done) {
    cap >> frame;
    if (frame.empty()) {
      std::cerr << "Error: Captured empty frame." << std::endl;
      continue;
    }

    {
      // INFO Capture lock for 1st queue i.e capture_Queue
      std::lock_guard<std::mutex> lock(capture_Mutex);
      capture_Queue.push(frame);
    } // INFO The lock_guard is released as soon as it goes out of scope.

    capture_CondVar.notify_one();
    // std::this_thread::_sleep_for(std::chrono::milliseconds(1));
  }
}

void processImage() {
#if ENABLE_PROFILING
  auto t1 = std::chrono::high_resolution_clock::now();
#endif

  while (!done) {
    cv::Mat frame;

    {
      std::unique_lock<std::mutex> lock(capture_Mutex);
      // INFO The capture_Mutex is used for capture_Queue object.
      capture_CondVar.wait(lock, [] { return !capture_Queue.empty() || done; });
      if (done && capture_Queue.empty())
        return;

      frame = capture_Queue.front();
      capture_Queue.pop();
    }

    cv::Mat processedFrame;
    // INFO Converting the image to grayscale.
    cv::cvtColor(frame, processedFrame, cv::COLOR_BGR2GRAY);

    {
      std::lock_guard<std::mutex> lock(process_Mutex);
      process_Queue.push(processedFrame);
    } // INFO The lock_guard is released as soon as it goes out of scope.

    process_CondVar.notify_one();
#if ENABLE_PROFILING
    total_frames += 1;
#endif
  }
#if ENABLE_PROFILING
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_taken = t2 - t1;
  double processing_latency = time_taken.count() / total_frames;
  double processing_throughput = 1 / processing_latency;
  std::cout << "processing function's throughput = " << processing_throughput
            << " Frames per second " << std::endl;
  std::cout << "processing function's latency = " << processing_latency
            << " Seconds per frame " << std::endl;
#endif
}

void displayImage() {
  int k = 0;
  while (!done) {
    cv::Mat frame;

    {
      std::unique_lock<std::mutex> lock(process_Mutex);
      // INFO The process_Mutex is used for capture_Queue object.
      process_CondVar.wait(lock, [] { return !process_Queue.empty() || done; });
      if (done && process_Queue.empty())
        return;

      frame = process_Queue.front();
      process_Queue.pop();
    }

    cv::imshow("Processed Image", frame);
    k = cv::waitKey(1);
    if (k == 27) { // Exit on ESC key
      done = true;
      break;
    }
  }
  cv::destroyAllWindows();
  cv::waitKey(1);
}

int pipeline_function() {

  std::thread captureThread(captureImage);
  std::thread processThread(processImage);
  std::thread displayThread(displayImage);

  // Join all the threads
  captureThread.join();
  processThread.join();
  displayThread.join();

  return 0;
}

#if BUILD_PYTHON_MODULE
#pragma message("Compiling the pybind11 module")
PYBIND11_MODULE(image_pipeline, m) {
  m.doc() = R"pbdoc(
            PyBind11 binding for multithreaded image processing and display function
            ------------------------------------------------------------------------
            
            .. currentmodule: binder_function

            .. autosummary::
               :toctree: _generate

               Runs a multithreaded image pipeline which takes an input, processes (grayscaling) and displays the processed image using opencv functions
  )pbdoc";

  m.def("pipeline_func", &pipeline_function, "core image pipeline function");
}
#endif
int main() {
#if ENABLE_PROFILING
  auto t1 = std::chrono::high_resolution_clock::now();
  pipeline_function();
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> total_time_take = t2 - t1;
  double latency = total_time_take.count() / total_frames;
  double throughput = 1 / latency;
  std::cout << "Pipeline Throughput = " << throughput << " Frames per second "
            << std::endl;
  std::cout << "Pipeline Latency = " << latency << " Seconds per frame "
            << std::endl;
#else
  pipeline_function();
#endif
  return 0;
}