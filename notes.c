#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace cv;
static volatile int state;

enum states {
	BEGINNING = 0x00,
	START_LINE = 0x03,
	MIDDLE = 0x04,
	END_LINE = 0x07,
	PAST_END = 0x08
};

Class EndlineCounter {
	private :
		ros::NodeHandle nh;
		
		image_transport::ImageTransport it;
		image_transport::Subscriber sub;
		
		cv_bridge::CvImagePtr imgptr;
		cv::Mat img;
		
		ros::Publisher pub;
	
	
	public :
		int state;
		
		EndlineCounter (ros::NodeHandle nh) : it(nh) 
		{
			sub = it.subscribe("tl_camera/image",1, &EndlineCounter::img_callback);
			nh.advertise<std_msgs::Bool>("endline",1);
			state = BEGINNING;
		}
		
		int get_state() {
			return state;
		}
		
		
}

EndlineCounter::img_callback(const sensor_msgs::ImagePtr& msg) {
	pub = nh.advertise<std_msgs::Bool>("endline", 1);
	imgptr = cv_bridge::toCvCopy(msg, "bgr8")->image); 
	
	//process image
	
	
	//publish 
	if(state & ENDLINE_PAST) {
		pub.publish(true);
	} else {
		pub.publish(false);
	}
}

void EndlineCounter::find_el_state() {
	
}


int main(int argc, char** argv)
{
	
	ros::init(argc,argv, "endline_counter");
	std::cout << "Initializing endline_counter" << endl;
	
	//nodehandler.param ?
	
	
	while(ros::ok)
	{
	
		
		ros::spinOnce();
	}

{