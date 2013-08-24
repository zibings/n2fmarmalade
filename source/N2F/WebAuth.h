#ifndef _WEBAUTH_H_
#define _WEBAUTH_H_

#include <cstdarg>
#include <string>
#include <vector>

#include "s3e.h"
#include "IwGx.h"
#include "s3eWebView.h"

namespace N2F
{
	namespace Iw3D
	{

		enum waState
		{
			// post construction default (clean)
			waClean,
			// some, but not all, required configuration is complete
			waConfiguring,
			// ready to navigate to the auth page
			waReady,
			// waiting for auth to complete
			waAuthorizing,
			// processing failure
			waProcessingFailure,
			// auth failed
			waAuthorizationFailed,
			// processing success
			waProcessingSuccess,
			// parse failed
			waParserFailure,
			// auth succeeded
			waAuthorizationSucceeded
		};

		class WebAuth
		{
		public:
			// construct a WebAuth object
			WebAuth();
			// must be called every 'tick'
			void update();
			// set the url to visit in order to start the authorization process (must be called before beginAuth) 
			void setAuthUrl(std::string authUrl);
			// set the url to which the webview will be returned if authorization is successful (must be called before beginAuth) 
			void setSuccessUrl(std::string successUrl);
			// set the url to which the webview will be returned if authorization fails (must be called before beginAuth) 
			void setFailureUrl(std::string failureUrl);
			// set the position of the top left corner of the webview (must be called before beginAuth) 
			void setPosition(float x, float y);
			// set the width and height of the webview (must be called before beginAuth) 
			void setSize(float w, float h);
			// add to the list of tokens to check for in the success url (must be called at least once before beginAuth) 
			void addArgToken(std::string token);
			// get the value of an arg (when isSuccessful returns true)
			std::string getArgValue(std::string token); 
			// start the process and show the webview
			void beginAuth();
			// bail on the process, hide the webview, and reset everything back to clean
			void reset();
			// is the object in the clean (pre-configure) state
			bool isClean();
			// is the object in the ready (post-configure) state
			bool isReady();
			// is the object waiting on the user to complete authorization
			bool isAuthorizing();
			// is the object processing the result of the authorization process
			bool isProcessing();
			// has the authorization process failed
			bool isFailed();
			// has the authorization process completed successfully
			bool isSuccessful();
			// get the current state of the object
			waState getState();

		protected:
			/* Object State */
			// state machine state
			waState myState;
			// reference to the s3eWebView
			s3eWebView *myWebView;
			// position and size of the s3eWebView
			float x, y, w, h;
			// is the s3eWebView visible
			bool myVisibility;

			/* Auth State */
			// the url to the page on the server which handles the authorization process
			std::string webAuthUrl;
			// the url to the page on the server which we will reach if authorization succeeds
			std::string successUrl;
			// the url to the page on the server which we will reach if authorization fails
			std::string failureUrl;
			// the url the webview has been redirected to
			std::string responseUrl;
			// the list of argument tokens to look for in the responseUrl
			std::vector<std::string> argTokenList;
			// the list of values parsed from the responseUrl
			std::vector<std::string> argValueList;
			// are the values in authToken and authSecret valid
			bool authValid;

			/* Internal Methods */
			// are we in a good state to take configuration
			bool canConfig();
			// do we have everything we need to complete configuration
			bool doneConfig();
			// put the object into the clean state
			void clean();
			// create the webview and send it to webAuthUrl
			void beginNav();
			// make the webview visible
			void show();
			// make the webview invisible
			void hide();
			// this should be called every time the webview begins to load a new url (use the callback wrapper)
			int32 loading(s3eWebView* instance, void* sysData, void* userData);
			// this should be called every time the webview finishes loading a new url (use the callback wrapper)
			int32 loaded(s3eWebView* instance, void* sysData, void* userData);
			// pull the named parameter out of the url and return it, or ''
			std::string extractParam(std::string url, const char *name);

			// debugging
			static void DebugOut(const char* format_url, ...);

	
			/* Callback Wrappers */
			// callback wrapper for loading - register it with the webview so it is called every time a url begins to load
			static int32 loadingCallback(s3eWebView* instance, void* sysData, void* userData);
			// callback wrapper for loaded - register it with the webview so it is called every time a url finished loading
			static int32 loadedCallback(s3eWebView* instance, void* sysData, void* userData);
		};

	};

};

#endif
