import unittest
import image_pipeline


class TestImagePipeline(unittest.TestCase):

    def test_pipeline_initialization_and_execution(self):
        """Test that the pipeline can initialize and execute without errors."""
        try:
            process = image_pipeline.pipeline_func()
            print(process)
        except Exception as e:
            self.fail(f"pipeline_func() raised an exception: {e}")


if __name__ == "__main__":
    unittest.main()
