# ifndef CustomApp_h
# define CustomApp_h

class CustomApp:public VisionApp_cl, public IVisCallbackHandler_cl
{
public:
	CustomApp(void);
	~CustomApp(void);
};

# endif //End Include Guard