#ifndef JS_reasings_GUARD
	#define JS_reasings_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <reasings.h>
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static JSValue js_EaseLinearNone(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseLinearNone(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseLinearIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseLinearIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseLinearOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseLinearOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseLinearInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseLinearInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseSineIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseSineIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseSineOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseSineOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseSineInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseSineInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCircIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCircIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCircOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCircOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCircInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCircInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCubicIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCubicIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCubicOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCubicOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseCubicInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseCubicInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseQuadIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseQuadIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseQuadOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseQuadOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseQuadInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseQuadInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseExpoIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseExpoIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseExpoOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseExpoOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseExpoInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseExpoInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBackIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBackIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBackOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBackOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBackInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBackInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBounceOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBounceOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBounceIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBounceIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseBounceInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseBounceInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseElasticIn(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseElasticIn(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseElasticOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseElasticOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_EaseElasticInOut(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float t=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float b=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float c=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float d=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=EaseElasticInOut(t,b,c,d);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	static const JSCFunctionListEntry jsreasings_funcs[]={
		JS_CFUNC_DEF("EaseLinearNone",4,js_EaseLinearNone),
		JS_CFUNC_DEF("EaseLinearIn",4,js_EaseLinearIn),
		JS_CFUNC_DEF("EaseLinearOut",4,js_EaseLinearOut),
		JS_CFUNC_DEF("EaseLinearInOut",4,js_EaseLinearInOut),
		JS_CFUNC_DEF("EaseSineIn",4,js_EaseSineIn),
		JS_CFUNC_DEF("EaseSineOut",4,js_EaseSineOut),
		JS_CFUNC_DEF("EaseSineInOut",4,js_EaseSineInOut),
		JS_CFUNC_DEF("EaseCircIn",4,js_EaseCircIn),
		JS_CFUNC_DEF("EaseCircOut",4,js_EaseCircOut),
		JS_CFUNC_DEF("EaseCircInOut",4,js_EaseCircInOut),
		JS_CFUNC_DEF("EaseCubicIn",4,js_EaseCubicIn),
		JS_CFUNC_DEF("EaseCubicOut",4,js_EaseCubicOut),
		JS_CFUNC_DEF("EaseCubicInOut",4,js_EaseCubicInOut),
		JS_CFUNC_DEF("EaseQuadIn",4,js_EaseQuadIn),
		JS_CFUNC_DEF("EaseQuadOut",4,js_EaseQuadOut),
		JS_CFUNC_DEF("EaseQuadInOut",4,js_EaseQuadInOut),
		JS_CFUNC_DEF("EaseExpoIn",4,js_EaseExpoIn),
		JS_CFUNC_DEF("EaseExpoOut",4,js_EaseExpoOut),
		JS_CFUNC_DEF("EaseExpoInOut",4,js_EaseExpoInOut),
		JS_CFUNC_DEF("EaseBackIn",4,js_EaseBackIn),
		JS_CFUNC_DEF("EaseBackOut",4,js_EaseBackOut),
		JS_CFUNC_DEF("EaseBackInOut",4,js_EaseBackInOut),
		JS_CFUNC_DEF("EaseBounceOut",4,js_EaseBounceOut),
		JS_CFUNC_DEF("EaseBounceIn",4,js_EaseBounceIn),
		JS_CFUNC_DEF("EaseBounceInOut",4,js_EaseBounceInOut),
		JS_CFUNC_DEF("EaseElasticIn",4,js_EaseElasticIn),
		JS_CFUNC_DEF("EaseElasticOut",4,js_EaseElasticOut),
		JS_CFUNC_DEF("EaseElasticInOut",4,js_EaseElasticInOut)
	};
	
	static int js_reasings_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsreasings_funcs);
		JS_SetModuleExportList(ctx,m,jsreasings_funcs,(int)listcount);
		return 0;
	}
	
	JSModuleDef * js_init_module_reasings(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_reasings_init);
		if(!m)return NULL;
		size_t listcount=countof(jsreasings_funcs);
		JS_AddModuleExportList(ctx,m,jsreasings_funcs,(int)listcount);
		return m;
	}

#endif //JS_reasings_GUARD