#include "WebAuth.h"

N2F::Iw3D::WebAuth::WebAuth()
{
	this->myWebView = NULL;
	this->clean();
}

void N2F::Iw3D::WebAuth::update()
{
	switch (myState)
	{
	case waClean:
		break;
	case waConfiguring:
		if(this->doneConfig())
		{
			this->myWebView = s3eWebViewCreate(false); // create a web view that does not have a transparent background
			/* Set up the callbacks */
			s3eWebViewRegister(S3E_WEBVIEW_STARTED_LOADING,  WebAuth::loadingCallback, this, this->myWebView);
			s3eWebViewRegister(S3E_WEBVIEW_FINISHED_LOADING, WebAuth::loadedCallback, this,  this->myWebView);
			this->myState = waReady;
		}
		break;
	case waReady:
		break;
	case waAuthorizing:
		break;
	case waProcessingFailure:
		// hide the webview
		this->hide();
		this->myState = waAuthorizationFailed;
		break;
	case waAuthorizationFailed:
		break;
	case waProcessingSuccess:
		// hide the webview
		this->hide();
		// try to parse stuff out of the responseUrl
		this->DebugOut("(waProcessingSuccess) responseUrl: %s", this->responseUrl.c_str());
		for(unsigned int i = 0; i < this->argTokenList.size(); i++)
		{
			this->argValueList.push_back(extractParam(this->responseUrl,this->argTokenList[i].c_str()));
			if(this->argValueList[i] == "")
			{
				// we failed to find a required parameter
				this->myState = waParserFailure;
				break;
			}
		}

		if (this->myState != waParserFailure)
		{
			this->authValid = true;
			this->myState = waAuthorizationSucceeded;
		}
		break;
	case waParserFailure:
		break;
	case waAuthorizationSucceeded:
		break;
	default:
		break;
	}
}

bool N2F::Iw3D::WebAuth::canConfig()
{
	return (this->myState == waClean || this->myState == waConfiguring);
}

bool N2F::Iw3D::WebAuth::doneConfig()
{
	// NOTE:  when all these are met, configuration phase automatically ends, locking all non-critical configuration
	//  This means, you should set position and size before setting these required values
	return (!this->webAuthUrl.empty()
		&& !this->successUrl.empty()
		&& !this->failureUrl.empty()
		&& this->argTokenList.size() > 0
		);
}

void N2F::Iw3D::WebAuth::setAuthUrl( std::string authUrl )
{
	if (this->canConfig())
	{
		this->webAuthUrl = authUrl.c_str();
		this->myState = waConfiguring;
		this->DebugOut("webAuthUrl set to: %s", this->webAuthUrl.c_str());
	}
	// otherwise, we are out of the config stage and should do nothing
}

void N2F::Iw3D::WebAuth::setSuccessUrl( std::string successUrl )
{
	if (this->canConfig())
	{
		this->successUrl = successUrl.c_str();
		this->myState = waConfiguring;
		this->DebugOut("successUrl set to: %s", this->successUrl.c_str());
	}
	// otherwise, we are out of the config stage and should do nothing

}

void N2F::Iw3D::WebAuth::setFailureUrl( std::string failureUrl )
{
	if (this->canConfig())
	{
		this->failureUrl = failureUrl.c_str();
		this->myState = waConfiguring;
		this->DebugOut("failureUrl set to: %s", this->failureUrl.c_str());
	}
	// otherwise, we are out of the config stage and should do nothing
}

void N2F::Iw3D::WebAuth::setPosition( float x, float y )
{
	if (this->canConfig())
	{
		this->x = x;
		this->y = y;
		this->myState = waConfiguring;
	}
	// otherwise, we are out of the config stage and should do nothing
}

void N2F::Iw3D::WebAuth::setSize( float w, float h )
{
	if (this->canConfig())
	{
		this->w = w;
		this->h = h;
		this->myState = waConfiguring;
	}
	// otherwise, we are out of the config stage and should do nothing
}

void N2F::Iw3D::WebAuth::addArgToken( std::string token )
{
	if (this->canConfig())
	{
		this->argTokenList.push_back(token);
		this->myState = waConfiguring;
		this->DebugOut("added arg token: %s", token.c_str());
	}
	// otherwise, we are out of the config stage and should do nothing
}

std::string N2F::Iw3D::WebAuth::getArgValue(std::string token)
{
	if (this->myState == waAuthorizationSucceeded)
	{
		for (unsigned int i = 0; i < this->argTokenList.size(); i++)
		{
			if(this->argTokenList[i] == token)
			{
				return this->argValueList[i];
			}
		}
	}

	return "";
}

void N2F::Iw3D::WebAuth::beginAuth()
{
	if (this->myState != waReady)
	{
		// calling this on an object which is not ready should have no effect
		return;
	}
	this->beginNav();
	this->show();

	this->myState = waAuthorizing;
}

void N2F::Iw3D::WebAuth::reset()
{
	this->hide();
	this->clean();
}

bool N2F::Iw3D::WebAuth::isClean()
{
	return (this->myState == waClean);
}

bool N2F::Iw3D::WebAuth::isReady()
{
	return (this->myState == waReady);
}

bool N2F::Iw3D::WebAuth::isAuthorizing()
{
	return (this->myState == waAuthorizing);
}

bool N2F::Iw3D::WebAuth::isProcessing()
{
	return (this->myState == waProcessingFailure || this->myState == waProcessingSuccess);
}

bool N2F::Iw3D::WebAuth::isFailed()
{
	return (this->myState == waParserFailure || this->myState == waAuthorizationFailed);
}

bool N2F::Iw3D::WebAuth::isSuccessful()
{
	return (this->myState == waAuthorizationSucceeded);
}

N2F::Iw3D::waState N2F::Iw3D::WebAuth::getState()
{
	return this->myState;
}

void N2F::Iw3D::WebAuth::clean()
{
	this->myState = waClean;
	if (this->myWebView != NULL)
	{
		s3eWebViewUnRegister(S3E_WEBVIEW_STARTED_LOADING,  WebAuth::loadingCallback, this->myWebView);
		s3eWebViewUnRegister(S3E_WEBVIEW_FINISHED_LOADING, WebAuth::loadedCallback, this->myWebView);
		s3eWebViewDestroy(this->myWebView);
	}
	this->myWebView = NULL;
	this->x = 0.0f;
	this->y = 0.0f;
	this->w = 0.0f;
	this->h = 0.0f;
	this->myVisibility = false;

	this->webAuthUrl.clear();
	this->successUrl.clear();
	this->failureUrl.clear();
	this->responseUrl = '\0';
	this->authValid = false;
}

void N2F::Iw3D::WebAuth::beginNav()
{
	s3eWebViewNavigate(this->myWebView, this->webAuthUrl.c_str());
}

void N2F::Iw3D::WebAuth::show()
{
	s3eWebViewShow(this->myWebView, (int)this->x, (int)this->y, (int)this->w, (int)this->h);
	this->myVisibility = true;
}

void N2F::Iw3D::WebAuth::hide()
{
	s3eWebViewHide(this->myWebView);
	this->myVisibility = false;
}

int32 N2F::Iw3D::WebAuth::loading( s3eWebView* instance, void* sysData, void* userData )
{
	std::string strUrl = (char*)sysData;

	this->DebugOut("strUrl: %s",     strUrl.c_str());
	this->DebugOut("webAuthUrl: %s", this->webAuthUrl.c_str());
	this->DebugOut("successUrl: %s", this->successUrl.c_str());
	this->DebugOut("failureUrl: %s", this->failureUrl.c_str());

	if (strUrl.find(this->webAuthUrl) != std::string::npos)
	{
		// starting the authorization process
	}
	if (strUrl.find(this->successUrl) != std::string::npos)
	{
		// successfully completing the authorization process
		this->responseUrl = strUrl;
		this->DebugOut("responseUrl: %s", this->responseUrl.c_str());
		this->myState = waProcessingSuccess;
	}
	if (strUrl.find(this->failureUrl) != std::string::npos)
	{
		// failing the authorization process
		this->myState = waProcessingFailure;
	}

	return 1;
}

int32 N2F::Iw3D::WebAuth::loaded( s3eWebView* instance, void* sysData, void* userData )
{
	// it is probably better to react on loading rather than wait for the page to fully load

	return 1;
}

std::string N2F::Iw3D::WebAuth::extractParam(std::string url, const char* name)
{
	std::string ret;
	size_t found = url.find(name);

	if (found != std::string::npos && found != 0 && (url.compare((found - 1), 1, "&") == 0 || url.compare((found - 1), 1, "?") == 0))
	{
		size_t eq = url.find("=", (found + 1));

		if (eq != std::string::npos)
		{
			size_t start = found + strlen(name) + 1;
			size_t amp = url.find("&", (eq + 1));

			if (amp != std::string::npos)
			{
				ret = url.substr(start, (amp - start));
			}
			else
			{
				ret = url.substr(start);
			}
		}
		else
		{
			this->DebugOut("Didn't find '=' after the %s token", name);
		}
	}
	else
	{
		this->DebugOut("Didn't find the %s token in this string: %s", name, url.c_str());
	}

	return(ret);
}

int32 N2F::Iw3D::WebAuth::loadingCallback(s3eWebView* instance, void* sysData, void* userData)
{
	WebAuth *self = static_cast<WebAuth *>(userData);
	return self->loading(instance, sysData, userData);
}

int32 N2F::Iw3D::WebAuth::loadedCallback( s3eWebView* instance, void* sysData, void* userData )
{
	WebAuth *self = static_cast<WebAuth *>(userData);
	return self->loaded(instance, sysData, userData);
}

void N2F::Iw3D::WebAuth::DebugOut(const char* format, ...)
{
	s3eDeviceYield(0);

	va_list args;
	const int buflen = 2048;
	char message[buflen];

	va_start(args, format);
	vsnprintf(message, buflen, format, args);
	va_end(args);

	s3eDebugOutputString(message);

	return;
}

