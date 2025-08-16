#ifndef JS_js_raygui_GUARD
	#define JS_js_raygui_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <rayjs_generated.h>
	#include <raylib.h>
#define RAYGUI_IMPLEMENTATION ;
	#include <raygui.h>
	
	static void js_GuiStyleProp_finalizer(JSRuntime * rt,JSValue val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque(val,js_GuiStyleProp_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_GuiStyleProp_get_controlId(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short controlId=ptr[0].controlId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)controlId));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_controlId(JSContext * ctx,JSValue this_val,JSValue v){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		uint32_t long_value;
		int err_value=JS_ToUint32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		unsigned short value=((unsigned short)long_value);
		ptr[0].controlId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiStyleProp_get_propertyId(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short propertyId=ptr[0].propertyId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)propertyId));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_propertyId(JSContext * ctx,JSValue this_val,JSValue v){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		uint32_t long_value;
		int err_value=JS_ToUint32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		unsigned short value=((unsigned short)long_value);
		ptr[0].propertyId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiStyleProp_get_propertyValue(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		int propertyValue=ptr[0].propertyValue;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)propertyValue));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_propertyValue(JSContext * ctx,JSValue this_val,JSValue v){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].propertyValue=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_GuiStyleProp_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","GuiStyleProp", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("controlId",js_GuiStyleProp_get_controlId,js_GuiStyleProp_set_controlId),
		JS_CGETSET_DEF("propertyId",js_GuiStyleProp_get_propertyId,js_GuiStyleProp_set_propertyId),
		JS_CGETSET_DEF("propertyValue",js_GuiStyleProp_get_propertyValue,js_GuiStyleProp_set_propertyValue)
	};
	
	static int js_declare_GuiStyleProp(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_GuiStyleProp_class_id);
		JSClassDef js_GuiStyleProp_def={ .class_name = "GuiStyleProp", .finalizer = js_GuiStyleProp_finalizer };
		JS_NewClass(rt,js_GuiStyleProp_class_id,(const JSClassDef *)&js_GuiStyleProp_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_GuiStyleProp_proto_funcs,(int)countof(js_GuiStyleProp_proto_funcs));
		JS_SetClassProto(ctx,js_GuiStyleProp_class_id,proto);
		return 0;
	}
	
	static JSValue js_GuiStyleProp_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			GuiStyleProp * ptr__return=(GuiStyleProp *)js_calloc(ctx,(size_t)1,sizeof(GuiStyleProp));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_GuiStyleProp_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		uint32_t long_controlId;
		int err_controlId=JS_ToUint32(ctx,&long_controlId,argv[0]);
		if(err_controlId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned short controlId=((unsigned short)long_controlId);
		uint32_t long_propertyId;
		int err_propertyId=JS_ToUint32(ctx,&long_propertyId,argv[1]);
		if(err_propertyId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned short propertyId=((unsigned short)long_propertyId);
		int32_t long_propertyValue;
		int err_propertyValue=JS_ToInt32(ctx,&long_propertyValue,argv[2]);
		if(err_propertyValue<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int propertyValue=((int)long_propertyValue);
		GuiStyleProp _struct={
			controlId,
			propertyId,
			propertyValue
		};
		GuiStyleProp * ptr__return=(GuiStyleProp *)js_malloc(ctx,sizeof(GuiStyleProp));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_GuiStyleProp_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_GuiEnable(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiEnable();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiDisable(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiDisable();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiLock(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiLock();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiUnlock(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiUnlock();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiIsLocked(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=GuiIsLocked();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GuiSetAlpha(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_alpha;
		int err_alpha=JS_ToFloat64(ctx,&double_alpha,argv[0]);
		if(err_alpha<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float alpha=((float)double_alpha);
		GuiSetAlpha(alpha);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiSetState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_state;
		int err_state=JS_ToInt32(ctx,&long_state,argv[0]);
		if(err_state<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int state=((int)long_state);
		GuiSetState(state);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GuiGetState();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSetFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Font * ptr_font=(Font *)JS_GetOpaque(argv[0],js_Font_class_id);
		if(ptr_font==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Font font=*ptr_font;
		GuiSetFont(font);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Font returnVal=GuiGetFont();
		Font * ptr_ret=(Font *)js_malloc(ctx,sizeof(Font));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Font_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GuiSetStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_control;
		int err_control=JS_ToInt32(ctx,&long_control,argv[0]);
		if(err_control<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int control=((int)long_control);
		int32_t long_property;
		int err_property=JS_ToInt32(ctx,&long_property,argv[1]);
		if(err_property<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int property=((int)long_property);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,argv[2]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		GuiSetStyle(control,property,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_control;
		int err_control=JS_ToInt32(ctx,&long_control,argv[0]);
		if(err_control<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int control=((int)long_control);
		int32_t long_property;
		int err_property=JS_ToInt32(ctx,&long_property,argv[1]);
		if(err_property<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int property=((int)long_property);
		int returnVal=GuiGetStyle(control,property);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLoadStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * fileName;
		JSValue da_fileName;
		int64_t size_fileName;
		if(JS_IsString(argv[0])==1){
			fileName =(char *)JS_ToCStringLen(ctx,(size_t *)&size_fileName,argv[0]);
		}else if(JS_IsArrayBuffer(argv[0])==1){
			fileName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fileName,argv[0]);
		}else{
			JSClassID classid_fileName=JS_GetClassID(argv[0]);
			if(classid_fileName==JS_CLASS_INT8_ARRAY){
				size_t offset_fileName;
				da_fileName =JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,(size_t *)&size_fileName,NULL);
				fileName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fileName,da_fileName);
				fileName +=offset_fileName;
				size_fileName -=offset_fileName;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		GuiLoadStyle((const char *)fileName);
		if(JS_IsArray(argv[0])==1){
			js_free(ctx,(void *)fileName);
		}else if(JS_IsString(argv[0])==1){
			JS_FreeCString(ctx,(const char *)fileName);
		}else{
			JSClassID classid_fileName=JS_GetClassID(argv[0]);
			if(classid_fileName==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_fileName);
			}
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiLoadStyleDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiLoadStyleDefault();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiEnableTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiEnableTooltip();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiDisableTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		GuiDisableTooltip();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiSetTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * tooltip;
		JSValue da_tooltip;
		int64_t size_tooltip;
		if(JS_IsString(argv[0])==1){
			tooltip =(char *)JS_ToCStringLen(ctx,(size_t *)&size_tooltip,argv[0]);
		}else if(JS_IsArrayBuffer(argv[0])==1){
			tooltip =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_tooltip,argv[0]);
		}else{
			JSClassID classid_tooltip=JS_GetClassID(argv[0]);
			if(classid_tooltip==JS_CLASS_INT8_ARRAY){
				size_t offset_tooltip;
				da_tooltip =JS_GetTypedArrayBuffer(ctx,argv[0],&offset_tooltip,(size_t *)&size_tooltip,NULL);
				tooltip =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_tooltip,da_tooltip);
				tooltip +=offset_tooltip;
				size_tooltip -=offset_tooltip;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		GuiSetTooltip((const char *)tooltip);
		if(JS_IsArray(argv[0])==1){
			js_free(ctx,(void *)tooltip);
		}else if(JS_IsString(argv[0])==1){
			JS_FreeCString(ctx,(const char *)tooltip);
		}else{
			JSClassID classid_tooltip=JS_GetClassID(argv[0]);
			if(classid_tooltip==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_tooltip);
			}
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiIconText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_iconId;
		int err_iconId=JS_ToInt32(ctx,&long_iconId,argv[0]);
		if(err_iconId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int iconId=((int)long_iconId);
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * returnVal=(char *)GuiIconText(iconId,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret;
		ret =JS_NewString(ctx,(const char *)returnVal);
		return ret;
	}
	
	static JSValue js_GuiSetIconScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_scale;
		int err_scale=JS_ToInt32(ctx,&long_scale,argv[0]);
		if(err_scale<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int scale=((int)long_scale);
		GuiSetIconScale(scale);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetIcons(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int * returnVal=GuiGetIcons();
		JSValue ret;
		ret =JS_NewArray(ctx);
		int * sizeref_ret=returnVal;
		size_t size_ret=sizeof(sizeref_ret);
		size_t size1_ret=sizeof(int);
		size_ret =size_ret/size1_ret;
		int i;
		for(i=0;i<size_ret;i++){
			JSValue js_ret=JS_NewInt32(ctx,(int32_t)((long)returnVal[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_GuiLoadIcons(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * fileName;
		JSValue da_fileName;
		int64_t size_fileName;
		if(JS_IsString(argv[0])==1){
			fileName =(char *)JS_ToCStringLen(ctx,(size_t *)&size_fileName,argv[0]);
		}else if(JS_IsArrayBuffer(argv[0])==1){
			fileName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fileName,argv[0]);
		}else{
			JSClassID classid_fileName=JS_GetClassID(argv[0]);
			if(classid_fileName==JS_CLASS_INT8_ARRAY){
				size_t offset_fileName;
				da_fileName =JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,(size_t *)&size_fileName,NULL);
				fileName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fileName,da_fileName);
				fileName +=offset_fileName;
				size_fileName -=offset_fileName;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int js_loadIconsName=JS_ToBool(ctx,argv[1]);
		if(js_loadIconsName<0){
			if(JS_IsArray(argv[0])==1){
				js_free(ctx,(void *)fileName);
			}else if(JS_IsString(argv[0])==1){
				JS_FreeCString(ctx,(const char *)fileName);
			}else{
				JSClassID classid_fileName=JS_GetClassID(argv[0]);
				if(classid_fileName==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_fileName);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not a bool");
			return JS_EXCEPTION;
		}
		bool loadIconsName=(bool)js_loadIconsName;
		char * * returnVal=GuiLoadIcons((const char *)fileName,loadIconsName);
		if(JS_IsArray(argv[0])==1){
			js_free(ctx,(void *)fileName);
		}else if(JS_IsString(argv[0])==1){
			JS_FreeCString(ctx,(const char *)fileName);
		}else{
			JSClassID classid_fileName=JS_GetClassID(argv[0]);
			if(classid_fileName==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_fileName);
			}
		}
		JSValue ret;
		ret =JS_NewArray(ctx);
		char * * sizeref_ret=returnVal;
		size_t size_ret=sizeof(sizeref_ret);
		size_t size1_ret=sizeof(char *);
		size_ret =size_ret/size1_ret;
		int i;
		for(i=0;i<size_ret;i++){
			JSValue js_ret;
			js_ret =JS_NewString(ctx,(const char *)returnVal[i]);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_GuiDrawIcon(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_iconId;
		int err_iconId=JS_ToInt32(ctx,&long_iconId,argv[0]);
		if(err_iconId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int iconId=((int)long_iconId);
		int32_t long_posX;
		int err_posX=JS_ToInt32(ctx,&long_posX,argv[1]);
		if(err_posX<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int posX=((int)long_posX);
		int32_t long_posY;
		int err_posY=JS_ToInt32(ctx,&long_posY,argv[2]);
		if(err_posY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int posY=((int)long_posY);
		int32_t long_pixelSize;
		int err_pixelSize=JS_ToInt32(ctx,&long_pixelSize,argv[3]);
		if(err_pixelSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int pixelSize=((int)long_pixelSize);
		Color * ptr_color=(Color *)JS_GetOpaque(argv[4],js_Color_class_id);
		if(ptr_color==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] does not allow null");
			return JS_EXCEPTION;
		}
		Color color=*ptr_color;
		GuiDrawIcon(iconId,posX,posY,pixelSize,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiWindowBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * title;
		JSValue da_title;
		int64_t size_title;
		if(JS_IsString(argv[1])==1){
			title =(char *)JS_ToCStringLen(ctx,(size_t *)&size_title,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,argv[1]);
		}else{
			JSClassID classid_title=JS_GetClassID(argv[1]);
			if(classid_title==JS_CLASS_INT8_ARRAY){
				size_t offset_title;
				da_title =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,(size_t *)&size_title,NULL);
				title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,da_title);
				title +=offset_title;
				size_title -=offset_title;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiWindowBox(bounds,(const char *)title);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)title);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)title);
		}else{
			JSClassID classid_title=JS_GetClassID(argv[1]);
			if(classid_title==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_title);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiGroupBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiGroupBox(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiLine(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiPanel(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiTabBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * * text;
		int64_t size_text;
		JSClassID text_class=JS_GetClassID(argv[1]);
		if(text_class==js_ArrayProxy_class_id){
			void * opaque_text=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_text=((ArrayProxy_class *)opaque_text)[0];
			argv[1] =AP_text.values(ctx,AP_text.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[1]);
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_text)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			text =(char * *)js_malloc(ctx,size_text*sizeof(char *));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)*text);
			int i;
			for(i=0;i<size_text;i++){
				JSValue js_text=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				int64_t size_texti;
				if(JS_IsString(js_text)==1){
					text[i] =(char *)JS_ToCStringLen(ctx,(size_t *)&size_texti,js_text);
					memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)text[i]);
				}else if(JS_IsArrayBuffer(js_text)==1){
					text[i] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_texti,js_text);
					memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)text[i]);
				}else{
					JSClassID classid_texti=JS_GetClassID(js_text);
					if(classid_texti==JS_CLASS_INT8_ARRAY){
						size_t offset_texti;
						JSValue da_texti=JS_GetTypedArrayBuffer(ctx,js_text,&offset_texti,(size_t *)&size_texti,NULL);
						text[i] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_texti,da_texti);
						text[i] +=offset_texti;
						size_texti -=offset_texti;
						memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_texti);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"js_text does not match type char *");
						return JS_EXCEPTION;
					}
				}
				JS_FreeValue(ctx,js_text);
			}
		}else{
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char * *");
			return JS_EXCEPTION;
		}
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[2]);
		if(err_count<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		int * active;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[3]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[3] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_active)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)active);
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[3]);
			if(err_js_active<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int returnVal=GuiTabBar(bounds,(const char * *)text,count,active);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiScrollPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		Rectangle * ptr_content=(Rectangle *)JS_GetOpaque(argv[2],js_Rectangle_class_id);
		if(ptr_content==NULL){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle content=*ptr_content;
		Vector2 * scroll=(Vector2 *)JS_GetOpaque(argv[3],js_Vector2_class_id);
		if(scroll==NULL){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type Vector2");
			return JS_EXCEPTION;
		}
		Rectangle * view=(Rectangle *)JS_GetOpaque(argv[4],js_Rectangle_class_id);
		if(view==NULL){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[4] does not match type Rectangle");
			return JS_EXCEPTION;
		}
		int returnVal=GuiScrollPanel(bounds,(const char *)text,content,scroll,view);
		JS_SetOpaque(argv[3],(void *)scroll);
		JS_SetOpaque(argv[4],(void *)view);
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLabel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiLabel(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiButton(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiButton(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLabelButton(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiLabelButton(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		bool * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[2]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[2] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			active =(bool *)js_malloc(ctx,size_active*sizeof(bool));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int js_activei=JS_ToBool(ctx,js_active);
				if(js_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not a bool");
					return JS_EXCEPTION;
				}
				active[i] =(bool)js_activei;
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int js_js_active=JS_ToBool(ctx,argv[2]);
			if(js_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
				return JS_EXCEPTION;
			}
			bool js_active=(bool)js_js_active;
			active =&js_active;
		}
		int returnVal=GuiToggle(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewBool(ctx,active[0]);
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggleGroup(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[2]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[2] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[2]);
			if(err_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int returnVal=GuiToggleGroup(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggleSlider(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[2]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[2] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[2]);
			if(err_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int returnVal=GuiToggleSlider(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiCheckBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		bool * checked;
		bool freesrc_checked=(bool)false;
		int64_t size_checked;
		JSClassID checked_class=JS_GetClassID(argv[2]);
		if(checked_class==js_ArrayProxy_class_id){
			void * opaque_checked=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_checked=((ArrayProxy_class *)opaque_checked)[0];
			argv[2] =AP_checked.values(ctx,AP_checked.opaque,(int)0,(bool)false);
			freesrc_checked =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_checked)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			checked =(bool *)js_malloc(ctx,size_checked*sizeof(bool));
			int i;
			for(i=0;i<size_checked;i++){
				JSValue js_checked=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int js_checkedi=JS_ToBool(ctx,js_checked);
				if(js_checkedi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_checked is not a bool");
					return JS_EXCEPTION;
				}
				checked[i] =(bool)js_checkedi;
				JS_FreeValue(ctx,js_checked);
			}
		}else{
			int js_js_checked=JS_ToBool(ctx,argv[2]);
			if(js_js_checked<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
				return JS_EXCEPTION;
			}
			bool js_checked=(bool)js_js_checked;
			checked =&js_checked;
		}
		int returnVal=GuiCheckBox(bounds,(const char *)text,checked);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewBool(ctx,checked[0]);
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)checked);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiComboBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[2]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[2] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[2]);
			if(err_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int returnVal=GuiComboBox(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiDropdownBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[2]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[2] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[2]);
			if(err_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int js_editMode=JS_ToBool(ctx,argv[3]);
		if(js_editMode<0){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)active);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool editMode=(bool)js_editMode;
		int returnVal=GuiDropdownBox(bounds,(const char *)text,active,editMode);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSpinner(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * value;
		bool freesrc_value=(bool)false;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[2]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[2] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_value)==-1){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			value =(int *)js_malloc(ctx,size_value*sizeof(int));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_valuei;
				int err_valuei=JS_ToInt32(ctx,&long_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((int)long_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			int32_t long_js_value;
			int err_js_value=JS_ToInt32(ctx,&long_js_value,argv[2]);
			if(err_js_value<0){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_value=((int)long_js_value);
			value =&js_value;
		}
		int32_t long_minValue;
		int err_minValue=JS_ToInt32(ctx,&long_minValue,argv[3]);
		if(err_minValue<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int minValue=((int)long_minValue);
		int32_t long_maxValue;
		int err_maxValue=JS_ToInt32(ctx,&long_maxValue,argv[4]);
		if(err_maxValue<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int maxValue=((int)long_maxValue);
		int js_editMode=JS_ToBool(ctx,argv[5]);
		if(js_editMode<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not a bool");
			return JS_EXCEPTION;
		}
		bool editMode=(bool)js_editMode;
		int returnVal=GuiSpinner(bounds,(const char *)text,value,minValue,maxValue,editMode);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)value);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiValueBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * value;
		bool freesrc_value=(bool)false;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[2]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[2] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_value)==-1){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			value =(int *)js_malloc(ctx,size_value*sizeof(int));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_valuei;
				int err_valuei=JS_ToInt32(ctx,&long_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((int)long_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			int32_t long_js_value;
			int err_js_value=JS_ToInt32(ctx,&long_js_value,argv[2]);
			if(err_js_value<0){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_value=((int)long_js_value);
			value =&js_value;
		}
		int32_t long_minValue;
		int err_minValue=JS_ToInt32(ctx,&long_minValue,argv[3]);
		if(err_minValue<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int minValue=((int)long_minValue);
		int32_t long_maxValue;
		int err_maxValue=JS_ToInt32(ctx,&long_maxValue,argv[4]);
		if(err_maxValue<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int maxValue=((int)long_maxValue);
		int js_editMode=JS_ToBool(ctx,argv[5]);
		if(js_editMode<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			if(JS_IsArray(argv[2])==1){
				js_free(ctx,(void *)value);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not a bool");
			return JS_EXCEPTION;
		}
		bool editMode=(bool)js_editMode;
		int returnVal=GuiValueBox(bounds,(const char *)text,value,minValue,maxValue,editMode);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)value);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiValueBoxFloat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)text);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				JSValue da_text=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_text);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * textValue;
		int64_t size_textValue;
		if(JS_IsString(argv[2])==1){
			textValue =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textValue,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textValue);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			textValue =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textValue,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textValue);
		}else{
			JSClassID classid_textValue=JS_GetClassID(argv[2]);
			if(classid_textValue==JS_CLASS_INT8_ARRAY){
				size_t offset_textValue;
				JSValue da_textValue=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textValue,(size_t *)&size_textValue,NULL);
				textValue =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textValue,da_textValue);
				textValue +=offset_textValue;
				size_textValue -=offset_textValue;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textValue);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[3]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[3] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_value)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			value =(float *)js_malloc(ctx,size_value*sizeof(float));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)value);
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			double double_js_value;
			int err_js_value=JS_ToFloat64(ctx,&double_js_value,argv[3]);
			if(err_js_value<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			float js_value=((float)double_js_value);
			value =&js_value;
		}
		int js_editMode=JS_ToBool(ctx,argv[4]);
		if(js_editMode<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not a bool");
			return JS_EXCEPTION;
		}
		bool editMode=(bool)js_editMode;
		int returnVal=GuiValueBoxFloat(bounds,(const char *)text,textValue,value,editMode);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewFloat64(ctx,((double)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiTextBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int32_t long_textSize;
		int err_textSize=JS_ToInt32(ctx,&long_textSize,argv[2]);
		if(err_textSize<0){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int textSize=((int)long_textSize);
		int js_editMode=JS_ToBool(ctx,argv[3]);
		if(js_editMode<0){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool editMode=(bool)js_editMode;
		int returnVal=GuiTextBox(bounds,text,textSize,editMode);
		if(JS_IsArray(argv[1])==1){
			argv[1] =JS_NewString(ctx,(const char *)text);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSlider(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * textLeft;
		int64_t size_textLeft;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			textLeft =NULL;
		}else if(JS_IsString(argv[1])==1){
			textLeft =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textLeft);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textLeft);
		}else{
			JSClassID classid_textLeft=JS_GetClassID(argv[1]);
			if(classid_textLeft==JS_CLASS_INT8_ARRAY){
				size_t offset_textLeft;
				JSValue da_textLeft=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,(size_t *)&size_textLeft,NULL);
				textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,da_textLeft);
				textLeft +=offset_textLeft;
				size_textLeft -=offset_textLeft;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textLeft);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * textRight;
		int64_t size_textRight;
		if(JS_IsString(argv[2])==1){
			textRight =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textRight);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textRight);
		}else{
			JSClassID classid_textRight=JS_GetClassID(argv[2]);
			if(classid_textRight==JS_CLASS_INT8_ARRAY){
				size_t offset_textRight;
				JSValue da_textRight=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,(size_t *)&size_textRight,NULL);
				textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,da_textRight);
				textRight +=offset_textRight;
				size_textRight -=offset_textRight;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textRight);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[3]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[3] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_value)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			value =(float *)js_malloc(ctx,size_value*sizeof(float));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)value);
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			double double_js_value;
			int err_js_value=JS_ToFloat64(ctx,&double_js_value,argv[3]);
			if(err_js_value<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			float js_value=((float)double_js_value);
			value =&js_value;
		}
		double double_minValue;
		int err_minValue=JS_ToFloat64(ctx,&double_minValue,argv[4]);
		if(err_minValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float minValue=((float)double_minValue);
		double double_maxValue;
		int err_maxValue=JS_ToFloat64(ctx,&double_maxValue,argv[5]);
		if(err_maxValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		float maxValue=((float)double_maxValue);
		int returnVal=GuiSlider(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewFloat64(ctx,((double)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSliderBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * textLeft;
		int64_t size_textLeft;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			textLeft =NULL;
		}else if(JS_IsString(argv[1])==1){
			textLeft =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textLeft);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textLeft);
		}else{
			JSClassID classid_textLeft=JS_GetClassID(argv[1]);
			if(classid_textLeft==JS_CLASS_INT8_ARRAY){
				size_t offset_textLeft;
				JSValue da_textLeft=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,(size_t *)&size_textLeft,NULL);
				textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,da_textLeft);
				textLeft +=offset_textLeft;
				size_textLeft -=offset_textLeft;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textLeft);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * textRight;
		int64_t size_textRight;
		if(JS_IsString(argv[2])==1){
			textRight =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textRight);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textRight);
		}else{
			JSClassID classid_textRight=JS_GetClassID(argv[2]);
			if(classid_textRight==JS_CLASS_INT8_ARRAY){
				size_t offset_textRight;
				JSValue da_textRight=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,(size_t *)&size_textRight,NULL);
				textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,da_textRight);
				textRight +=offset_textRight;
				size_textRight -=offset_textRight;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textRight);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[3]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[3] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_value)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			value =(float *)js_malloc(ctx,size_value*sizeof(float));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)value);
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			double double_js_value;
			int err_js_value=JS_ToFloat64(ctx,&double_js_value,argv[3]);
			if(err_js_value<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			float js_value=((float)double_js_value);
			value =&js_value;
		}
		double double_minValue;
		int err_minValue=JS_ToFloat64(ctx,&double_minValue,argv[4]);
		if(err_minValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float minValue=((float)double_minValue);
		double double_maxValue;
		int err_maxValue=JS_ToFloat64(ctx,&double_maxValue,argv[5]);
		if(err_maxValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		float maxValue=((float)double_maxValue);
		int returnVal=GuiSliderBar(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewFloat64(ctx,((double)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiProgressBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * textLeft;
		int64_t size_textLeft;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			textLeft =NULL;
		}else if(JS_IsString(argv[1])==1){
			textLeft =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textLeft);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textLeft);
		}else{
			JSClassID classid_textLeft=JS_GetClassID(argv[1]);
			if(classid_textLeft==JS_CLASS_INT8_ARRAY){
				size_t offset_textLeft;
				JSValue da_textLeft=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,(size_t *)&size_textLeft,NULL);
				textLeft =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textLeft,da_textLeft);
				textLeft +=offset_textLeft;
				size_textLeft -=offset_textLeft;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textLeft);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * textRight;
		int64_t size_textRight;
		if(JS_IsString(argv[2])==1){
			textRight =(char *)JS_ToCStringLen(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)textRight);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)textRight);
		}else{
			JSClassID classid_textRight=JS_GetClassID(argv[2]);
			if(classid_textRight==JS_CLASS_INT8_ARRAY){
				size_t offset_textRight;
				JSValue da_textRight=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,(size_t *)&size_textRight,NULL);
				textRight =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_textRight,da_textRight);
				textRight +=offset_textRight;
				size_textRight -=offset_textRight;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_textRight);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[3]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[3] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_value)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			value =(float *)js_malloc(ctx,size_value*sizeof(float));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)value);
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			double double_js_value;
			int err_js_value=JS_ToFloat64(ctx,&double_js_value,argv[3]);
			if(err_js_value<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			float js_value=((float)double_js_value);
			value =&js_value;
		}
		double double_minValue;
		int err_minValue=JS_ToFloat64(ctx,&double_minValue,argv[4]);
		if(err_minValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float minValue=((float)double_minValue);
		double double_maxValue;
		int err_maxValue=JS_ToFloat64(ctx,&double_maxValue,argv[5]);
		if(err_maxValue<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		float maxValue=((float)double_maxValue);
		int returnVal=GuiProgressBar(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewFloat64(ctx,((double)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiStatusBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiStatusBar(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiDummyRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiDummyRec(bounds,(const char *)text);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiGrid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		double double_spacing;
		int err_spacing=JS_ToFloat64(ctx,&double_spacing,argv[2]);
		if(err_spacing<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float spacing=((float)double_spacing);
		int32_t long_subdivs;
		int err_subdivs=JS_ToInt32(ctx,&long_subdivs,argv[3]);
		if(err_subdivs<0){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int subdivs=((int)long_subdivs);
		Vector2 * mouseCell=(Vector2 *)JS_GetOpaque(argv[4],js_Vector2_class_id);
		if(mouseCell==NULL){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[4] does not match type Vector2");
			return JS_EXCEPTION;
		}
		int returnVal=GuiGrid(bounds,(const char *)text,spacing,subdivs,mouseCell);
		JS_SetOpaque(argv[4],(void *)mouseCell);
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiListView(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int * scrollIndex;
		bool freesrc_scrollIndex=(bool)false;
		int64_t size_scrollIndex;
		JSClassID scrollIndex_class=JS_GetClassID(argv[2]);
		if(scrollIndex_class==js_ArrayProxy_class_id){
			void * opaque_scrollIndex=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_scrollIndex=((ArrayProxy_class *)opaque_scrollIndex)[0];
			argv[2] =AP_scrollIndex.values(ctx,AP_scrollIndex.opaque,(int)0,(bool)false);
			freesrc_scrollIndex =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_scrollIndex)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			scrollIndex =(int *)js_malloc(ctx,size_scrollIndex*sizeof(int));
			int i;
			for(i=0;i<size_scrollIndex;i++){
				JSValue js_scrollIndex=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				int32_t long_scrollIndexi;
				int err_scrollIndexi=JS_ToInt32(ctx,&long_scrollIndexi,js_scrollIndex);
				if(err_scrollIndexi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_scrollIndex is not numeric");
					return JS_EXCEPTION;
				}
				scrollIndex[i] =((int)long_scrollIndexi);
				JS_FreeValue(ctx,js_scrollIndex);
			}
		}else{
			int32_t long_js_scrollIndex;
			int err_js_scrollIndex=JS_ToInt32(ctx,&long_js_scrollIndex,argv[2]);
			if(err_js_scrollIndex<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			int js_scrollIndex=((int)long_js_scrollIndex);
			scrollIndex =&js_scrollIndex;
		}
		int * active;
		bool freesrc_active=(bool)false;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[3]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[3] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			freesrc_active =(bool)true;
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_active)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				if(JS_IsArray(argv[2])==1){
					js_free(ctx,(void *)scrollIndex);
				}
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[3]);
			if(err_js_active<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				if(JS_IsArray(argv[2])==1){
					js_free(ctx,(void *)scrollIndex);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int returnVal=GuiListView(bounds,(const char *)text,scrollIndex,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewInt32(ctx,(int32_t)((long)scrollIndex[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)scrollIndex);
		}
		if(JS_IsArray(argv[3])==1){
			js_free(ctx,(void *)active);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiListViewEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * * text;
		int64_t size_text;
		JSClassID text_class=JS_GetClassID(argv[1]);
		if(text_class==js_ArrayProxy_class_id){
			void * opaque_text=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_text=((ArrayProxy_class *)opaque_text)[0];
			argv[1] =AP_text.values(ctx,AP_text.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[1]);
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_text)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			text =(char * *)js_malloc(ctx,size_text*sizeof(char *));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)*text);
			int i;
			for(i=0;i<size_text;i++){
				JSValue js_text=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				int64_t size_texti;
				if(JS_IsString(js_text)==1){
					text[i] =(char *)JS_ToCStringLen(ctx,(size_t *)&size_texti,js_text);
					memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)text[i]);
				}else if(JS_IsArrayBuffer(js_text)==1){
					text[i] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_texti,js_text);
					memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)text[i]);
				}else{
					JSClassID classid_texti=JS_GetClassID(js_text);
					if(classid_texti==JS_CLASS_INT8_ARRAY){
						size_t offset_texti;
						JSValue da_texti=JS_GetTypedArrayBuffer(ctx,js_text,&offset_texti,(size_t *)&size_texti,NULL);
						text[i] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_texti,da_texti);
						text[i] +=offset_texti;
						size_texti -=offset_texti;
						memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_texti);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"js_text does not match type char *");
						return JS_EXCEPTION;
					}
				}
				JS_FreeValue(ctx,js_text);
			}
		}else{
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char * *");
			return JS_EXCEPTION;
		}
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[2]);
		if(err_count<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		int * scrollIndex;
		int64_t size_scrollIndex;
		JSClassID scrollIndex_class=JS_GetClassID(argv[3]);
		if(scrollIndex_class==js_ArrayProxy_class_id){
			void * opaque_scrollIndex=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_scrollIndex=((ArrayProxy_class *)opaque_scrollIndex)[0];
			argv[3] =AP_scrollIndex.values(ctx,AP_scrollIndex.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_scrollIndex)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			scrollIndex =(int *)js_malloc(ctx,size_scrollIndex*sizeof(int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)scrollIndex);
			int i;
			for(i=0;i<size_scrollIndex;i++){
				JSValue js_scrollIndex=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				int32_t long_scrollIndexi;
				int err_scrollIndexi=JS_ToInt32(ctx,&long_scrollIndexi,js_scrollIndex);
				if(err_scrollIndexi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_scrollIndex is not numeric");
					return JS_EXCEPTION;
				}
				scrollIndex[i] =((int)long_scrollIndexi);
				JS_FreeValue(ctx,js_scrollIndex);
			}
		}else{
			int32_t long_js_scrollIndex;
			int err_js_scrollIndex=JS_ToInt32(ctx,&long_js_scrollIndex,argv[3]);
			if(err_js_scrollIndex<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
				return JS_EXCEPTION;
			}
			int js_scrollIndex=((int)long_js_scrollIndex);
			scrollIndex =&js_scrollIndex;
		}
		int * active;
		int64_t size_active;
		JSClassID active_class=JS_GetClassID(argv[4]);
		if(active_class==js_ArrayProxy_class_id){
			void * opaque_active=JS_GetOpaque(argv[4],js_ArrayProxy_class_id);
			ArrayProxy_class AP_active=((ArrayProxy_class *)opaque_active)[0];
			argv[4] =AP_active.values(ctx,AP_active.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[4]);
		}else if(JS_IsArray(argv[4])==1){
			if(JS_GetLength(ctx,argv[4],&size_active)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			active =(int *)js_malloc(ctx,size_active*sizeof(int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)active);
			int i;
			for(i=0;i<size_active;i++){
				JSValue js_active=JS_GetPropertyUint32(ctx,argv[4],(uint32_t)i);
				int32_t long_activei;
				int err_activei=JS_ToInt32(ctx,&long_activei,js_active);
				if(err_activei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_active is not numeric");
					return JS_EXCEPTION;
				}
				active[i] =((int)long_activei);
				JS_FreeValue(ctx,js_active);
			}
		}else{
			int32_t long_js_active;
			int err_js_active=JS_ToInt32(ctx,&long_js_active,argv[4]);
			if(err_js_active<0){
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
				return JS_EXCEPTION;
			}
			int js_active=((int)long_js_active);
			active =&js_active;
		}
		int * focus;
		int64_t size_focus;
		JSClassID focus_class=JS_GetClassID(argv[5]);
		if(focus_class==js_ArrayProxy_class_id){
			void * opaque_focus=JS_GetOpaque(argv[5],js_ArrayProxy_class_id);
			ArrayProxy_class AP_focus=((ArrayProxy_class *)opaque_focus)[0];
			argv[5] =AP_focus.values(ctx,AP_focus.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[5]);
		}else if(JS_IsArray(argv[5])==1){
			if(JS_GetLength(ctx,argv[5],&size_focus)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			focus =(int *)js_malloc(ctx,size_focus*sizeof(int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)focus);
			int i;
			for(i=0;i<size_focus;i++){
				JSValue js_focus=JS_GetPropertyUint32(ctx,argv[5],(uint32_t)i);
				int32_t long_focusi;
				int err_focusi=JS_ToInt32(ctx,&long_focusi,js_focus);
				if(err_focusi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_focus is not numeric");
					return JS_EXCEPTION;
				}
				focus[i] =((int)long_focusi);
				JS_FreeValue(ctx,js_focus);
			}
		}else if(JS_IsArrayBuffer(argv[5])==1){
			focus =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_focus,argv[5]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)focus);
		}else{
			JSClassID classid_focus=JS_GetClassID(argv[5]);
			if(classid_focus==JS_CLASS_INT16_ARRAY){
				size_t offset_focus;
				JSValue da_focus=JS_GetTypedArrayBuffer(ctx,argv[5],&offset_focus,(size_t *)&size_focus,NULL);
				focus =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_focus,da_focus);
				focus +=offset_focus;
				size_focus -=offset_focus;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_focus);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[5] does not match type int *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiListViewEx(bounds,(const char * *)text,count,scrollIndex,active,focus);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv3=JS_NewInt32(ctx,(int32_t)((long)scrollIndex[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv3,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[4])==1){
			JSValue js_argv4=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[4],(uint32_t)0,js_argv4,JS_PROP_C_W_E);
		}
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiMessageBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * title;
		int64_t size_title;
		if(JS_IsString(argv[1])==1){
			title =(char *)JS_ToCStringLen(ctx,(size_t *)&size_title,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)title);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)title);
		}else{
			JSClassID classid_title=JS_GetClassID(argv[1]);
			if(classid_title==JS_CLASS_INT8_ARRAY){
				size_t offset_title;
				JSValue da_title=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,(size_t *)&size_title,NULL);
				title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,da_title);
				title +=offset_title;
				size_title -=offset_title;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_title);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * message;
		int64_t size_message;
		if(JS_IsString(argv[2])==1){
			message =(char *)JS_ToCStringLen(ctx,(size_t *)&size_message,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)message);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			message =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_message,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)message);
		}else{
			JSClassID classid_message=JS_GetClassID(argv[2]);
			if(classid_message==JS_CLASS_INT8_ARRAY){
				size_t offset_message;
				JSValue da_message=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,(size_t *)&size_message,NULL);
				message =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_message,da_message);
				message +=offset_message;
				size_message -=offset_message;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_message);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * buttons;
		int64_t size_buttons;
		if(JS_IsString(argv[3])==1){
			buttons =(char *)JS_ToCStringLen(ctx,(size_t *)&size_buttons,argv[3]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)buttons);
		}else if(JS_IsArrayBuffer(argv[3])==1){
			buttons =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_buttons,argv[3]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)buttons);
		}else{
			JSClassID classid_buttons=JS_GetClassID(argv[3]);
			if(classid_buttons==JS_CLASS_INT8_ARRAY){
				size_t offset_buttons;
				JSValue da_buttons=JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,(size_t *)&size_buttons,NULL);
				buttons =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_buttons,da_buttons);
				buttons +=offset_buttons;
				size_buttons -=offset_buttons;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_buttons);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=GuiMessageBox(bounds,(const char *)title,(const char *)message,(const char *)buttons);
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiTextInputBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * title;
		int64_t size_title;
		if(JS_IsString(argv[1])==1){
			title =(char *)JS_ToCStringLen(ctx,(size_t *)&size_title,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)title);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)title);
		}else{
			JSClassID classid_title=JS_GetClassID(argv[1]);
			if(classid_title==JS_CLASS_INT8_ARRAY){
				size_t offset_title;
				JSValue da_title=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,(size_t *)&size_title,NULL);
				title =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_title,da_title);
				title +=offset_title;
				size_title -=offset_title;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_title);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * message;
		int64_t size_message;
		if(JS_IsString(argv[2])==1){
			message =(char *)JS_ToCStringLen(ctx,(size_t *)&size_message,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)message);
		}else if(JS_IsArrayBuffer(argv[2])==1){
			message =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_message,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)message);
		}else{
			JSClassID classid_message=JS_GetClassID(argv[2]);
			if(classid_message==JS_CLASS_INT8_ARRAY){
				size_t offset_message;
				JSValue da_message=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,(size_t *)&size_message,NULL);
				message =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_message,da_message);
				message +=offset_message;
				size_message -=offset_message;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_message);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * buttons;
		int64_t size_buttons;
		if(JS_IsString(argv[3])==1){
			buttons =(char *)JS_ToCStringLen(ctx,(size_t *)&size_buttons,argv[3]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)buttons);
		}else if(JS_IsArrayBuffer(argv[3])==1){
			buttons =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_buttons,argv[3]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)buttons);
		}else{
			JSClassID classid_buttons=JS_GetClassID(argv[3]);
			if(classid_buttons==JS_CLASS_INT8_ARRAY){
				size_t offset_buttons;
				JSValue da_buttons=JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,(size_t *)&size_buttons,NULL);
				buttons =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_buttons,da_buttons);
				buttons +=offset_buttons;
				size_buttons -=offset_buttons;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_buttons);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * text;
		int64_t size_text;
		if(JS_IsString(argv[4])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[4]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)text);
		}else if(JS_IsArrayBuffer(argv[4])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[4]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[4]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				JSValue da_text=JS_GetTypedArrayBuffer(ctx,argv[4],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_text);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[4] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int32_t long_textMaxSize;
		int err_textMaxSize=JS_ToInt32(ctx,&long_textMaxSize,argv[5]);
		if(err_textMaxSize<0){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		int textMaxSize=((int)long_textMaxSize);
		bool * secretViewActive;
		int64_t size_secretViewActive;
		JSClassID secretViewActive_class=JS_GetClassID(argv[6]);
		if(JS_IsNull(argv[6])||JS_IsUndefined(argv[6])){
			secretViewActive =NULL;
		}else if(secretViewActive_class==js_ArrayProxy_class_id){
			void * opaque_secretViewActive=JS_GetOpaque(argv[6],js_ArrayProxy_class_id);
			ArrayProxy_class AP_secretViewActive=((ArrayProxy_class *)opaque_secretViewActive)[0];
			argv[6] =AP_secretViewActive.values(ctx,AP_secretViewActive.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[6]);
		}else if(JS_IsArray(argv[6])==1){
			if(JS_GetLength(ctx,argv[6],&size_secretViewActive)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			secretViewActive =(bool *)js_malloc(ctx,size_secretViewActive*sizeof(bool));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)secretViewActive);
			int i;
			for(i=0;i<size_secretViewActive;i++){
				JSValue js_secretViewActive=JS_GetPropertyUint32(ctx,argv[6],(uint32_t)i);
				int js_secretViewActivei=JS_ToBool(ctx,js_secretViewActive);
				if(js_secretViewActivei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_secretViewActive is not a bool");
					return JS_EXCEPTION;
				}
				secretViewActive[i] =(bool)js_secretViewActivei;
				JS_FreeValue(ctx,js_secretViewActive);
			}
		}else if(JS_IsArrayBuffer(argv[6])==1){
			secretViewActive =(bool *)JS_GetArrayBuffer(ctx,(size_t *)&size_secretViewActive,argv[6]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)secretViewActive);
		}else{
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[6] does not match type bool *");
			return JS_EXCEPTION;
		}
		int returnVal=GuiTextInputBox(bounds,(const char *)title,(const char *)message,(const char *)buttons,text,textMaxSize,secretViewActive);
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPicker(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		Color * color=(Color *)JS_GetOpaque(argv[2],js_Color_class_id);
		if(color==NULL){
			if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			}
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type Color");
			return JS_EXCEPTION;
		}
		int returnVal=GuiColorPicker(bounds,(const char *)text,color);
		JS_SetOpaque(argv[2],(void *)color);
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		Color * color=(Color *)JS_GetOpaque(argv[2],js_Color_class_id);
		if(color==NULL){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type Color");
			return JS_EXCEPTION;
		}
		int returnVal=GuiColorPanel(bounds,(const char *)text,color);
		JS_SetOpaque(argv[2],(void *)color);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorBarAlpha(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
			text =NULL;
		}else if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * alpha;
		bool freesrc_alpha=(bool)false;
		int64_t size_alpha;
		JSClassID alpha_class=JS_GetClassID(argv[2]);
		if(alpha_class==js_ArrayProxy_class_id){
			void * opaque_alpha=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_alpha=((ArrayProxy_class *)opaque_alpha)[0];
			argv[2] =AP_alpha.values(ctx,AP_alpha.opaque,(int)0,(bool)false);
			freesrc_alpha =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_alpha)==-1){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			alpha =(float *)js_malloc(ctx,size_alpha*sizeof(float));
			int i;
			for(i=0;i<size_alpha;i++){
				JSValue js_alpha=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				double double_alphai;
				int err_alphai=JS_ToFloat64(ctx,&double_alphai,js_alpha);
				if(err_alphai<0){
					JS_ThrowTypeError(ctx,(const char *)"js_alpha is not numeric");
					return JS_EXCEPTION;
				}
				alpha[i] =((float)double_alphai);
				JS_FreeValue(ctx,js_alpha);
			}
		}else{
			double double_js_alpha;
			int err_js_alpha=JS_ToFloat64(ctx,&double_js_alpha,argv[2]);
			if(err_js_alpha<0){
				if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
				}
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			float js_alpha=((float)double_js_alpha);
			alpha =&js_alpha;
		}
		int returnVal=GuiColorBarAlpha(bounds,(const char *)text,alpha);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewFloat64(ctx,((double)alpha[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsNull(argv[1])||JS_IsUndefined(argv[1])){
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)alpha);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorBarHue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		float * value;
		bool freesrc_value=(bool)false;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(argv[2]);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			argv[2] =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_value)==-1){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				return JS_EXCEPTION;
			}
			value =(float *)js_malloc(ctx,size_value*sizeof(float));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else{
			double double_js_value;
			int err_js_value=JS_ToFloat64(ctx,&double_js_value,argv[2]);
			if(err_js_value<0){
				if(JS_IsArray(argv[1])==1){
					js_free(ctx,(void *)text);
				}else if(JS_IsString(argv[1])==1){
					JS_FreeCString(ctx,(const char *)text);
				}else{
					JSClassID classid_text=JS_GetClassID(argv[1]);
					if(classid_text==JS_CLASS_INT8_ARRAY){
						js_free(ctx,(void *)&da_text);
					}
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
				return JS_EXCEPTION;
			}
			float js_value=((float)double_js_value);
			value =&js_value;
		}
		int returnVal=GuiColorBarHue(bounds,(const char *)text,value);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv2=JS_NewFloat64(ctx,((double)value[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv2,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		if(JS_IsArray(argv[2])==1){
			js_free(ctx,(void *)value);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPickerHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		Vector3 * colorHsv=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(colorHsv==NULL){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type Vector3");
			return JS_EXCEPTION;
		}
		int returnVal=GuiColorPickerHSV(bounds,(const char *)text,colorHsv);
		JS_SetOpaque(argv[2],(void *)colorHsv);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPanelHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle * ptr_bounds=(Rectangle *)JS_GetOpaque(argv[0],js_Rectangle_class_id);
		if(ptr_bounds==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Rectangle bounds=*ptr_bounds;
		char * text;
		JSValue da_text;
		int64_t size_text;
		if(JS_IsString(argv[1])==1){
			text =(char *)JS_ToCStringLen(ctx,(size_t *)&size_text,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,argv[1]);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				size_t offset_text;
				da_text =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,(size_t *)&size_text,NULL);
				text =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_text,da_text);
				text +=offset_text;
				size_text -=offset_text;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		Vector3 * colorHsv=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(colorHsv==NULL){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)text);
			}else if(JS_IsString(argv[1])==1){
				JS_FreeCString(ctx,(const char *)text);
			}else{
				JSClassID classid_text=JS_GetClassID(argv[1]);
				if(classid_text==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_text);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type Vector3");
			return JS_EXCEPTION;
		}
		int returnVal=GuiColorPanelHSV(bounds,(const char *)text,colorHsv);
		JS_SetOpaque(argv[2],(void *)colorHsv);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)text);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)text);
		}else{
			JSClassID classid_text=JS_GetClassID(argv[1]);
			if(classid_text==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_text);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	static const JSCFunctionListEntry jsraygui_funcs[]={
		JS_CFUNC_DEF("GuiEnable",0,js_GuiEnable),
		JS_CFUNC_DEF("GuiDisable",0,js_GuiDisable),
		JS_CFUNC_DEF("GuiLock",0,js_GuiLock),
		JS_CFUNC_DEF("GuiUnlock",0,js_GuiUnlock),
		JS_CFUNC_DEF("GuiIsLocked",0,js_GuiIsLocked),
		JS_CFUNC_DEF("GuiSetAlpha",1,js_GuiSetAlpha),
		JS_CFUNC_DEF("GuiSetState",1,js_GuiSetState),
		JS_CFUNC_DEF("GuiGetState",0,js_GuiGetState),
		JS_CFUNC_DEF("GuiSetFont",1,js_GuiSetFont),
		JS_CFUNC_DEF("GuiGetFont",0,js_GuiGetFont),
		JS_CFUNC_DEF("GuiSetStyle",3,js_GuiSetStyle),
		JS_CFUNC_DEF("GuiGetStyle",2,js_GuiGetStyle),
		JS_CFUNC_DEF("GuiLoadStyle",1,js_GuiLoadStyle),
		JS_CFUNC_DEF("GuiLoadStyleDefault",0,js_GuiLoadStyleDefault),
		JS_CFUNC_DEF("GuiEnableTooltip",0,js_GuiEnableTooltip),
		JS_CFUNC_DEF("GuiDisableTooltip",0,js_GuiDisableTooltip),
		JS_CFUNC_DEF("GuiSetTooltip",1,js_GuiSetTooltip),
		JS_CFUNC_DEF("GuiIconText",2,js_GuiIconText),
		JS_CFUNC_DEF("GuiSetIconScale",1,js_GuiSetIconScale),
		JS_CFUNC_DEF("GuiGetIcons",0,js_GuiGetIcons),
		JS_CFUNC_DEF("GuiLoadIcons",2,js_GuiLoadIcons),
		JS_CFUNC_DEF("GuiDrawIcon",5,js_GuiDrawIcon),
		JS_CFUNC_DEF("GuiWindowBox",2,js_GuiWindowBox),
		JS_CFUNC_DEF("GuiGroupBox",2,js_GuiGroupBox),
		JS_CFUNC_DEF("GuiLine",2,js_GuiLine),
		JS_CFUNC_DEF("GuiPanel",2,js_GuiPanel),
		JS_CFUNC_DEF("GuiTabBar",4,js_GuiTabBar),
		JS_CFUNC_DEF("GuiScrollPanel",5,js_GuiScrollPanel),
		JS_CFUNC_DEF("GuiLabel",2,js_GuiLabel),
		JS_CFUNC_DEF("GuiButton",2,js_GuiButton),
		JS_CFUNC_DEF("GuiLabelButton",2,js_GuiLabelButton),
		JS_CFUNC_DEF("GuiToggle",3,js_GuiToggle),
		JS_CFUNC_DEF("GuiToggleGroup",3,js_GuiToggleGroup),
		JS_CFUNC_DEF("GuiToggleSlider",3,js_GuiToggleSlider),
		JS_CFUNC_DEF("GuiCheckBox",3,js_GuiCheckBox),
		JS_CFUNC_DEF("GuiComboBox",3,js_GuiComboBox),
		JS_CFUNC_DEF("GuiDropdownBox",4,js_GuiDropdownBox),
		JS_CFUNC_DEF("GuiSpinner",6,js_GuiSpinner),
		JS_CFUNC_DEF("GuiValueBox",6,js_GuiValueBox),
		JS_CFUNC_DEF("GuiValueBoxFloat",5,js_GuiValueBoxFloat),
		JS_CFUNC_DEF("GuiTextBox",4,js_GuiTextBox),
		JS_CFUNC_DEF("GuiSlider",6,js_GuiSlider),
		JS_CFUNC_DEF("GuiSliderBar",6,js_GuiSliderBar),
		JS_CFUNC_DEF("GuiProgressBar",6,js_GuiProgressBar),
		JS_CFUNC_DEF("GuiStatusBar",2,js_GuiStatusBar),
		JS_CFUNC_DEF("GuiDummyRec",2,js_GuiDummyRec),
		JS_CFUNC_DEF("GuiGrid",5,js_GuiGrid),
		JS_CFUNC_DEF("GuiListView",4,js_GuiListView),
		JS_CFUNC_DEF("GuiListViewEx",6,js_GuiListViewEx),
		JS_CFUNC_DEF("GuiMessageBox",4,js_GuiMessageBox),
		JS_CFUNC_DEF("GuiTextInputBox",7,js_GuiTextInputBox),
		JS_CFUNC_DEF("GuiColorPicker",3,js_GuiColorPicker),
		JS_CFUNC_DEF("GuiColorPanel",3,js_GuiColorPanel),
		JS_CFUNC_DEF("GuiColorBarAlpha",3,js_GuiColorBarAlpha),
		JS_CFUNC_DEF("GuiColorBarHue",3,js_GuiColorBarHue),
		JS_CFUNC_DEF("GuiColorPickerHSV",3,js_GuiColorPickerHSV),
		JS_CFUNC_DEF("GuiColorPanelHSV",3,js_GuiColorPanelHSV)
	};
	
	static int js_js_raygui_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsraygui_funcs);
		JS_SetModuleExportList(ctx,m,jsraygui_funcs,(int)listcount);
		js_declare_GuiStyleProp(ctx,m);
		JSValue GuiStyleProp_constr=JS_NewCFunction2(ctx,js_GuiStyleProp_constructor,(const char *)"GuiStyleProp",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"GuiStyleProp",GuiStyleProp_constr);
		JS_SetModuleExport(ctx,m,(const char *)"STATE_NORMAL",JS_NewInt32(ctx,(int32_t)STATE_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_FOCUSED",JS_NewInt32(ctx,(int32_t)STATE_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_PRESSED",JS_NewInt32(ctx,(int32_t)STATE_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_DISABLED",JS_NewInt32(ctx,(int32_t)STATE_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_LEFT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_CENTER",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_RIGHT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_TOP",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_MIDDLE",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_MIDDLE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_BOTTOM",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_NONE",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_NONE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_CHAR",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_CHAR));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_WORD",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_WORD));
		JS_SetModuleExport(ctx,m,(const char *)"DEFAULT",JS_NewInt32(ctx,(int32_t)DEFAULT));
		JS_SetModuleExport(ctx,m,(const char *)"LABEL",JS_NewInt32(ctx,(int32_t)LABEL));
		JS_SetModuleExport(ctx,m,(const char *)"BUTTON",JS_NewInt32(ctx,(int32_t)BUTTON));
		JS_SetModuleExport(ctx,m,(const char *)"TOGGLE",JS_NewInt32(ctx,(int32_t)TOGGLE));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER",JS_NewInt32(ctx,(int32_t)SLIDER));
		JS_SetModuleExport(ctx,m,(const char *)"PROGRESSBAR",JS_NewInt32(ctx,(int32_t)PROGRESSBAR));
		JS_SetModuleExport(ctx,m,(const char *)"CHECKBOX",JS_NewInt32(ctx,(int32_t)CHECKBOX));
		JS_SetModuleExport(ctx,m,(const char *)"COMBOBOX",JS_NewInt32(ctx,(int32_t)COMBOBOX));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWNBOX",JS_NewInt32(ctx,(int32_t)DROPDOWNBOX));
		JS_SetModuleExport(ctx,m,(const char *)"TEXTBOX",JS_NewInt32(ctx,(int32_t)TEXTBOX));
		JS_SetModuleExport(ctx,m,(const char *)"VALUEBOX",JS_NewInt32(ctx,(int32_t)VALUEBOX));
		JS_SetModuleExport(ctx,m,(const char *)"CONTROL11",JS_NewInt32(ctx,(int32_t)CONTROL11));
		JS_SetModuleExport(ctx,m,(const char *)"LISTVIEW",JS_NewInt32(ctx,(int32_t)LISTVIEW));
		JS_SetModuleExport(ctx,m,(const char *)"COLORPICKER",JS_NewInt32(ctx,(int32_t)COLORPICKER));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR",JS_NewInt32(ctx,(int32_t)SCROLLBAR));
		JS_SetModuleExport(ctx,m,(const char *)"STATUSBAR",JS_NewInt32(ctx,(int32_t)STATUSBAR));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)BASE_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_WIDTH",JS_NewInt32(ctx,(int32_t)BORDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_PADDING",JS_NewInt32(ctx,(int32_t)TEXT_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGNMENT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_SIZE",JS_NewInt32(ctx,(int32_t)TEXT_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_SPACING",JS_NewInt32(ctx,(int32_t)TEXT_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"LINE_COLOR",JS_NewInt32(ctx,(int32_t)LINE_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"BACKGROUND_COLOR",JS_NewInt32(ctx,(int32_t)BACKGROUND_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_LINE_SPACING",JS_NewInt32(ctx,(int32_t)TEXT_LINE_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT_VERTICAL",JS_NewInt32(ctx,(int32_t)TEXT_ALIGNMENT_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_MODE",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_MODE));
		JS_SetModuleExport(ctx,m,(const char *)"GROUP_PADDING",JS_NewInt32(ctx,(int32_t)GROUP_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER_WIDTH",JS_NewInt32(ctx,(int32_t)SLIDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER_PADDING",JS_NewInt32(ctx,(int32_t)SLIDER_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"PROGRESS_PADDING",JS_NewInt32(ctx,(int32_t)PROGRESS_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"ARROWS_SIZE",JS_NewInt32(ctx,(int32_t)ARROWS_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ARROWS_VISIBLE",JS_NewInt32(ctx,(int32_t)ARROWS_VISIBLE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_PADDING",JS_NewInt32(ctx,(int32_t)SCROLL_SLIDER_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_SIZE",JS_NewInt32(ctx,(int32_t)SCROLL_SLIDER_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_PADDING",JS_NewInt32(ctx,(int32_t)SCROLL_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SPEED",JS_NewInt32(ctx,(int32_t)SCROLL_SPEED));
		JS_SetModuleExport(ctx,m,(const char *)"CHECK_PADDING",JS_NewInt32(ctx,(int32_t)CHECK_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"COMBO_BUTTON_WIDTH",JS_NewInt32(ctx,(int32_t)COMBO_BUTTON_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"COMBO_BUTTON_SPACING",JS_NewInt32(ctx,(int32_t)COMBO_BUTTON_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"ARROW_PADDING",JS_NewInt32(ctx,(int32_t)ARROW_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ITEMS_SPACING",JS_NewInt32(ctx,(int32_t)DROPDOWN_ITEMS_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ARROW_HIDDEN",JS_NewInt32(ctx,(int32_t)DROPDOWN_ARROW_HIDDEN));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ROLL_UP",JS_NewInt32(ctx,(int32_t)DROPDOWN_ROLL_UP));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_READONLY",JS_NewInt32(ctx,(int32_t)TEXT_READONLY));
		JS_SetModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_WIDTH",JS_NewInt32(ctx,(int32_t)SPINNER_BUTTON_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_SPACING",JS_NewInt32(ctx,(int32_t)SPINNER_BUTTON_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_HEIGHT",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_SPACING",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_WIDTH",JS_NewInt32(ctx,(int32_t)SCROLLBAR_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_SIDE));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_NORMAL",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_BORDER_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_WIDTH",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_BORDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"COLOR_SELECTOR_SIZE",JS_NewInt32(ctx,(int32_t)COLOR_SELECTOR_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_WIDTH",JS_NewInt32(ctx,(int32_t)HUEBAR_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_PADDING",JS_NewInt32(ctx,(int32_t)HUEBAR_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_HEIGHT",JS_NewInt32(ctx,(int32_t)HUEBAR_SELECTOR_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_OVERFLOW",JS_NewInt32(ctx,(int32_t)HUEBAR_SELECTOR_OVERFLOW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NONE",JS_NewInt32(ctx,(int32_t)ICON_NONE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_FILE_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_FILE_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_FILE_SAVE_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_SAVE",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_SAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FILE_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE",JS_NewInt32(ctx,(int32_t)ICON_FILE_SAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_EXPORT",JS_NewInt32(ctx,(int32_t)ICON_FILE_EXPORT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_ADD",JS_NewInt32(ctx,(int32_t)ICON_FILE_ADD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_DELETE",JS_NewInt32(ctx,(int32_t)ICON_FILE_DELETE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_TEXT",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_TEXT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_AUDIO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_AUDIO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_IMAGE",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_IMAGE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_PLAY",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_PLAY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_VIDEO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_VIDEO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_INFO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_INFO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_COPY",JS_NewInt32(ctx,(int32_t)ICON_FILE_COPY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_CUT",JS_NewInt32(ctx,(int32_t)ICON_FILE_CUT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_PASTE",JS_NewInt32(ctx,(int32_t)ICON_FILE_PASTE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_HAND",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_HAND));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_POINTER",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_POINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PENCIL",JS_NewInt32(ctx,(int32_t)ICON_PENCIL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PENCIL_BIG",JS_NewInt32(ctx,(int32_t)ICON_PENCIL_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BRUSH_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_BRUSH_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BRUSH_PAINTER",JS_NewInt32(ctx,(int32_t)ICON_BRUSH_PAINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WATER_DROP",JS_NewInt32(ctx,(int32_t)ICON_WATER_DROP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLOR_PICKER",JS_NewInt32(ctx,(int32_t)ICON_COLOR_PICKER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RUBBER",JS_NewInt32(ctx,(int32_t)ICON_RUBBER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLOR_BUCKET",JS_NewInt32(ctx,(int32_t)ICON_COLOR_BUCKET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_T",JS_NewInt32(ctx,(int32_t)ICON_TEXT_T));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_A",JS_NewInt32(ctx,(int32_t)ICON_TEXT_A));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SCALE",JS_NewInt32(ctx,(int32_t)ICON_SCALE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RESIZE",JS_NewInt32(ctx,(int32_t)ICON_RESIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_POINT",JS_NewInt32(ctx,(int32_t)ICON_FILTER_POINT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_BILINEAR",JS_NewInt32(ctx,(int32_t)ICON_FILTER_BILINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROP",JS_NewInt32(ctx,(int32_t)ICON_CROP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROP_ALPHA",JS_NewInt32(ctx,(int32_t)ICON_CROP_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SQUARE_TOGGLE",JS_NewInt32(ctx,(int32_t)ICON_SQUARE_TOGGLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_HORIZONTAL",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY_HORIZONTAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_VERTICAL",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LENS",JS_NewInt32(ctx,(int32_t)ICON_LENS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LENS_BIG",JS_NewInt32(ctx,(int32_t)ICON_LENS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EYE_ON",JS_NewInt32(ctx,(int32_t)ICON_EYE_ON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EYE_OFF",JS_NewInt32(ctx,(int32_t)ICON_EYE_OFF));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_TOP",JS_NewInt32(ctx,(int32_t)ICON_FILTER_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER",JS_NewInt32(ctx,(int32_t)ICON_FILTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_POINT",JS_NewInt32(ctx,(int32_t)ICON_TARGET_POINT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG",JS_NewInt32(ctx,(int32_t)ICON_TARGET_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE",JS_NewInt32(ctx,(int32_t)ICON_TARGET_MOVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_MOVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_UNDO",JS_NewInt32(ctx,(int32_t)ICON_UNDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REDO",JS_NewInt32(ctx,(int32_t)ICON_REDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REREDO",JS_NewInt32(ctx,(int32_t)ICON_REREDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MUTATE",JS_NewInt32(ctx,(int32_t)ICON_MUTATE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROTATE",JS_NewInt32(ctx,(int32_t)ICON_ROTATE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REPEAT",JS_NewInt32(ctx,(int32_t)ICON_REPEAT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHUFFLE",JS_NewInt32(ctx,(int32_t)ICON_SHUFFLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX",JS_NewInt32(ctx,(int32_t)ICON_EMPTYBOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET",JS_NewInt32(ctx,(int32_t)ICON_TARGET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_SMALL_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_BIG_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_MOVE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_MOVE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_RIGHT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_LEFT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_UNDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_UNDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_REDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REREDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_REREDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MUTATE_FILL",JS_NewInt32(ctx,(int32_t)ICON_MUTATE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROTATE_FILL",JS_NewInt32(ctx,(int32_t)ICON_ROTATE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REPEAT_FILL",JS_NewInt32(ctx,(int32_t)ICON_REPEAT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHUFFLE_FILL",JS_NewInt32(ctx,(int32_t)ICON_SHUFFLE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX_SMALL",JS_NewInt32(ctx,(int32_t)ICON_EMPTYBOX_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX",JS_NewInt32(ctx,(int32_t)ICON_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CENTER",JS_NewInt32(ctx,(int32_t)ICON_BOX_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CIRCLE_MASK",JS_NewInt32(ctx,(int32_t)ICON_BOX_CIRCLE_MASK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_POT",JS_NewInt32(ctx,(int32_t)ICON_POT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALPHA_MULTIPLY",JS_NewInt32(ctx,(int32_t)ICON_ALPHA_MULTIPLY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALPHA_CLEAR",JS_NewInt32(ctx,(int32_t)ICON_ALPHA_CLEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DITHERING",JS_NewInt32(ctx,(int32_t)ICON_DITHERING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MIPMAPS",JS_NewInt32(ctx,(int32_t)ICON_MIPMAPS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_GRID",JS_NewInt32(ctx,(int32_t)ICON_BOX_GRID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GRID",JS_NewInt32(ctx,(int32_t)ICON_GRID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_BOX_CORNERS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_CORNERS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOUR_BOXES",JS_NewInt32(ctx,(int32_t)ICON_FOUR_BOXES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GRID_FILL",JS_NewInt32(ctx,(int32_t)ICON_GRID_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_MULTISIZE",JS_NewInt32(ctx,(int32_t)ICON_BOX_MULTISIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_SMALL",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_MEDIUM",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_MEDIUM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_BIG",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_ALL",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_ALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_CENTER",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_BOX_DOTS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_DOTS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CONCENTRIC",JS_NewInt32(ctx,(int32_t)ICON_BOX_CONCENTRIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_GRID_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_GRID_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_OK_TICK",JS_NewInt32(ctx,(int32_t)ICON_OK_TICK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSS",JS_NewInt32(ctx,(int32_t)ICON_CROSS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT",JS_NewInt32(ctx,(int32_t)ICON_ARROW_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_ARROW_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN",JS_NewInt32(ctx,(int32_t)ICON_ARROW_DOWN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_UP",JS_NewInt32(ctx,(int32_t)ICON_ARROW_UP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_LEFT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_RIGHT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_DOWN_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_UP_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_UP_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_AUDIO",JS_NewInt32(ctx,(int32_t)ICON_AUDIO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FX",JS_NewInt32(ctx,(int32_t)ICON_FX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE",JS_NewInt32(ctx,(int32_t)ICON_WAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_SINUS",JS_NewInt32(ctx,(int32_t)ICON_WAVE_SINUS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_SQUARE",JS_NewInt32(ctx,(int32_t)ICON_WAVE_SQUARE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_TRIANGULAR",JS_NewInt32(ctx,(int32_t)ICON_WAVE_TRIANGULAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_CROSS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PREVIOUS",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PREVIOUS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY_BACK",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PLAY_BACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PLAY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PAUSE",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PAUSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_STOP",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_STOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_NEXT",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_NEXT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_RECORD",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_RECORD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAGNET",JS_NewInt32(ctx,(int32_t)ICON_MAGNET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LOCK_CLOSE",JS_NewInt32(ctx,(int32_t)ICON_LOCK_CLOSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LOCK_OPEN",JS_NewInt32(ctx,(int32_t)ICON_LOCK_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CLOCK",JS_NewInt32(ctx,(int32_t)ICON_CLOCK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TOOLS",JS_NewInt32(ctx,(int32_t)ICON_TOOLS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR",JS_NewInt32(ctx,(int32_t)ICON_GEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR_BIG",JS_NewInt32(ctx,(int32_t)ICON_GEAR_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BIN",JS_NewInt32(ctx,(int32_t)ICON_BIN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HAND_POINTER",JS_NewInt32(ctx,(int32_t)ICON_HAND_POINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LASER",JS_NewInt32(ctx,(int32_t)ICON_LASER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COIN",JS_NewInt32(ctx,(int32_t)ICON_COIN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EXPLOSION",JS_NewInt32(ctx,(int32_t)ICON_EXPLOSION));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_1UP",JS_NewInt32(ctx,(int32_t)ICON_1UP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER",JS_NewInt32(ctx,(int32_t)ICON_PLAYER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_JUMP",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_JUMP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_KEY",JS_NewInt32(ctx,(int32_t)ICON_KEY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DEMON",JS_NewInt32(ctx,(int32_t)ICON_DEMON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_POPUP",JS_NewInt32(ctx,(int32_t)ICON_TEXT_POPUP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR_EX",JS_NewInt32(ctx,(int32_t)ICON_GEAR_EX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CRACK",JS_NewInt32(ctx,(int32_t)ICON_CRACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CRACK_POINTS",JS_NewInt32(ctx,(int32_t)ICON_CRACK_POINTS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STAR",JS_NewInt32(ctx,(int32_t)ICON_STAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DOOR",JS_NewInt32(ctx,(int32_t)ICON_DOOR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EXIT",JS_NewInt32(ctx,(int32_t)ICON_EXIT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MODE_2D",JS_NewInt32(ctx,(int32_t)ICON_MODE_2D));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MODE_3D",JS_NewInt32(ctx,(int32_t)ICON_MODE_3D));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE",JS_NewInt32(ctx,(int32_t)ICON_CUBE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_TOP",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_LEFT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_FRONT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_FRONT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BOTTOM",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BACK",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_BACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CAMERA",JS_NewInt32(ctx,(int32_t)ICON_CAMERA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SPECIAL",JS_NewInt32(ctx,(int32_t)ICON_SPECIAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_NET",JS_NewInt32(ctx,(int32_t)ICON_LINK_NET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_BOXES",JS_NewInt32(ctx,(int32_t)ICON_LINK_BOXES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_MULTI",JS_NewInt32(ctx,(int32_t)ICON_LINK_MULTI));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK",JS_NewInt32(ctx,(int32_t)ICON_LINK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_BROKE",JS_NewInt32(ctx,(int32_t)ICON_LINK_BROKE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_NOTES",JS_NewInt32(ctx,(int32_t)ICON_TEXT_NOTES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NOTEBOOK",JS_NewInt32(ctx,(int32_t)ICON_NOTEBOOK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SUITCASE",JS_NewInt32(ctx,(int32_t)ICON_SUITCASE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SUITCASE_ZIP",JS_NewInt32(ctx,(int32_t)ICON_SUITCASE_ZIP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAILBOX",JS_NewInt32(ctx,(int32_t)ICON_MAILBOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MONITOR",JS_NewInt32(ctx,(int32_t)ICON_MONITOR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PRINTER",JS_NewInt32(ctx,(int32_t)ICON_PRINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA",JS_NewInt32(ctx,(int32_t)ICON_PHOTO_CAMERA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA_FLASH",JS_NewInt32(ctx,(int32_t)ICON_PHOTO_CAMERA_FLASH));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HOUSE",JS_NewInt32(ctx,(int32_t)ICON_HOUSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HEART",JS_NewInt32(ctx,(int32_t)ICON_HEART));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CORNER",JS_NewInt32(ctx,(int32_t)ICON_CORNER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS",JS_NewInt32(ctx,(int32_t)ICON_VERTICAL_BARS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS_FILL",JS_NewInt32(ctx,(int32_t)ICON_VERTICAL_BARS_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LIFE_BARS",JS_NewInt32(ctx,(int32_t)ICON_LIFE_BARS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_INFO",JS_NewInt32(ctx,(int32_t)ICON_INFO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSSLINE",JS_NewInt32(ctx,(int32_t)ICON_CROSSLINE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HELP",JS_NewInt32(ctx,(int32_t)ICON_HELP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_ALPHA",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_HOME",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_HOME));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS_VISIBLE",JS_NewInt32(ctx,(int32_t)ICON_LAYERS_VISIBLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS",JS_NewInt32(ctx,(int32_t)ICON_LAYERS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WINDOW",JS_NewInt32(ctx,(int32_t)ICON_WINDOW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HIDPI",JS_NewInt32(ctx,(int32_t)ICON_HIDPI));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_BINARY",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_BINARY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HEX",JS_NewInt32(ctx,(int32_t)ICON_HEX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHIELD",JS_NewInt32(ctx,(int32_t)ICON_SHIELD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_NEW",JS_NewInt32(ctx,(int32_t)ICON_FILE_NEW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_ADD",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_ADD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALARM",JS_NewInt32(ctx,(int32_t)ICON_ALARM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CPU",JS_NewInt32(ctx,(int32_t)ICON_CPU));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROM",JS_NewInt32(ctx,(int32_t)ICON_ROM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_OVER",JS_NewInt32(ctx,(int32_t)ICON_STEP_OVER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_INTO",JS_NewInt32(ctx,(int32_t)ICON_STEP_INTO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_OUT",JS_NewInt32(ctx,(int32_t)ICON_STEP_OUT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RESTART",JS_NewInt32(ctx,(int32_t)ICON_RESTART));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_ON",JS_NewInt32(ctx,(int32_t)ICON_BREAKPOINT_ON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_OFF",JS_NewInt32(ctx,(int32_t)ICON_BREAKPOINT_OFF));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BURGER_MENU",JS_NewInt32(ctx,(int32_t)ICON_BURGER_MENU));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CASE_SENSITIVE",JS_NewInt32(ctx,(int32_t)ICON_CASE_SENSITIVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REG_EXP",JS_NewInt32(ctx,(int32_t)ICON_REG_EXP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER",JS_NewInt32(ctx,(int32_t)ICON_FOLDER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE",JS_NewInt32(ctx,(int32_t)ICON_FILE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SAND_TIMER",JS_NewInt32(ctx,(int32_t)ICON_SAND_TIMER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WARNING",JS_NewInt32(ctx,(int32_t)ICON_WARNING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HELP_BOX",JS_NewInt32(ctx,(int32_t)ICON_HELP_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_INFO_BOX",JS_NewInt32(ctx,(int32_t)ICON_INFO_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PRIORITY",JS_NewInt32(ctx,(int32_t)ICON_PRIORITY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS_ISO",JS_NewInt32(ctx,(int32_t)ICON_LAYERS_ISO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS2",JS_NewInt32(ctx,(int32_t)ICON_LAYERS2));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MLAYERS",JS_NewInt32(ctx,(int32_t)ICON_MLAYERS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAPS",JS_NewInt32(ctx,(int32_t)ICON_MAPS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HOT",JS_NewInt32(ctx,(int32_t)ICON_HOT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LABEL",JS_NewInt32(ctx,(int32_t)ICON_LABEL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NAME_ID",JS_NewInt32(ctx,(int32_t)ICON_NAME_ID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SLICING",JS_NewInt32(ctx,(int32_t)ICON_SLICING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MANUAL_CONTROL",JS_NewInt32(ctx,(int32_t)ICON_MANUAL_CONTROL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLLISION",JS_NewInt32(ctx,(int32_t)ICON_COLLISION));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_234",JS_NewInt32(ctx,(int32_t)ICON_234));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_235",JS_NewInt32(ctx,(int32_t)ICON_235));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_236",JS_NewInt32(ctx,(int32_t)ICON_236));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_237",JS_NewInt32(ctx,(int32_t)ICON_237));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_238",JS_NewInt32(ctx,(int32_t)ICON_238));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_239",JS_NewInt32(ctx,(int32_t)ICON_239));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_240",JS_NewInt32(ctx,(int32_t)ICON_240));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_241",JS_NewInt32(ctx,(int32_t)ICON_241));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_242",JS_NewInt32(ctx,(int32_t)ICON_242));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_243",JS_NewInt32(ctx,(int32_t)ICON_243));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_244",JS_NewInt32(ctx,(int32_t)ICON_244));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_245",JS_NewInt32(ctx,(int32_t)ICON_245));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_246",JS_NewInt32(ctx,(int32_t)ICON_246));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_247",JS_NewInt32(ctx,(int32_t)ICON_247));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_248",JS_NewInt32(ctx,(int32_t)ICON_248));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_249",JS_NewInt32(ctx,(int32_t)ICON_249));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_250",JS_NewInt32(ctx,(int32_t)ICON_250));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_251",JS_NewInt32(ctx,(int32_t)ICON_251));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_252",JS_NewInt32(ctx,(int32_t)ICON_252));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_253",JS_NewInt32(ctx,(int32_t)ICON_253));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_254",JS_NewInt32(ctx,(int32_t)ICON_254));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_255",JS_NewInt32(ctx,(int32_t)ICON_255));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MAJOR",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_MAJOR));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MINOR",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_MINOR));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_PATCH",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_PATCH));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_LEFT_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_LEFT_SIDE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_RIGHT_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_RIGHT_SIDE));
		return 0;
	}
	
	JSModuleDef * js_init_module_js_raygui(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_js_raygui_init);
		if(!m){
			return NULL;
		}
		size_t listcount=countof(jsraygui_funcs);
		JS_AddModuleExportList(ctx,m,jsraygui_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"GuiStyleProp");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_MIDDLE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_NONE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_CHAR");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_WORD");
		JS_AddModuleExport(ctx,m,(const char *)"DEFAULT");
		JS_AddModuleExport(ctx,m,(const char *)"LABEL");
		JS_AddModuleExport(ctx,m,(const char *)"BUTTON");
		JS_AddModuleExport(ctx,m,(const char *)"TOGGLE");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER");
		JS_AddModuleExport(ctx,m,(const char *)"PROGRESSBAR");
		JS_AddModuleExport(ctx,m,(const char *)"CHECKBOX");
		JS_AddModuleExport(ctx,m,(const char *)"COMBOBOX");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWNBOX");
		JS_AddModuleExport(ctx,m,(const char *)"TEXTBOX");
		JS_AddModuleExport(ctx,m,(const char *)"VALUEBOX");
		JS_AddModuleExport(ctx,m,(const char *)"CONTROL11");
		JS_AddModuleExport(ctx,m,(const char *)"LISTVIEW");
		JS_AddModuleExport(ctx,m,(const char *)"COLORPICKER");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR");
		JS_AddModuleExport(ctx,m,(const char *)"STATUSBAR");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"LINE_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"BACKGROUND_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_LINE_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_MODE");
		JS_AddModuleExport(ctx,m,(const char *)"GROUP_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"PROGRESS_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"ARROWS_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ARROWS_VISIBLE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SPEED");
		JS_AddModuleExport(ctx,m,(const char *)"CHECK_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"COMBO_BUTTON_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"COMBO_BUTTON_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"ARROW_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ITEMS_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ARROW_HIDDEN");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ROLL_UP");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_READONLY");
		JS_AddModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_SIDE");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"COLOR_SELECTOR_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_OVERFLOW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NONE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_FILE_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_SAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_EXPORT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_ADD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_DELETE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_TEXT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_AUDIO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_IMAGE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_PLAY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_VIDEO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_INFO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_COPY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_CUT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_PASTE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_HAND");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_POINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PENCIL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PENCIL_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BRUSH_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BRUSH_PAINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WATER_DROP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLOR_PICKER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RUBBER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLOR_BUCKET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_T");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_A");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SCALE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RESIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_POINT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_BILINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROP_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SQUARE_TOGGLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_HORIZONTAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LENS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LENS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EYE_ON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EYE_OFF");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_POINT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_UNDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REREDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MUTATE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROTATE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REPEAT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHUFFLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_UNDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REREDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MUTATE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROTATE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REPEAT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHUFFLE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CIRCLE_MASK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_POT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALPHA_MULTIPLY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALPHA_CLEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DITHERING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MIPMAPS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_GRID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GRID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOUR_BOXES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GRID_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_MULTISIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_MEDIUM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_ALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CONCENTRIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_GRID_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_OK_TICK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_UP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_UP_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_AUDIO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_SINUS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_SQUARE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_TRIANGULAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PREVIOUS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY_BACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PAUSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_STOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_NEXT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_RECORD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAGNET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LOCK_CLOSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LOCK_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CLOCK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TOOLS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BIN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HAND_POINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LASER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COIN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EXPLOSION");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_1UP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_JUMP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_KEY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DEMON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_POPUP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR_EX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CRACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CRACK_POINTS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DOOR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EXIT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MODE_2D");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MODE_3D");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_FRONT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CAMERA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SPECIAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_NET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_BOXES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_MULTI");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_BROKE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_NOTES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NOTEBOOK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SUITCASE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SUITCASE_ZIP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAILBOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MONITOR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PRINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA_FLASH");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HOUSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HEART");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CORNER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LIFE_BARS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_INFO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSSLINE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HELP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_HOME");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS_VISIBLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WINDOW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HIDPI");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_BINARY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HEX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHIELD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_NEW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_ADD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALARM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CPU");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_OVER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_INTO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_OUT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RESTART");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_ON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_OFF");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BURGER_MENU");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CASE_SENSITIVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REG_EXP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SAND_TIMER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WARNING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HELP_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_INFO_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PRIORITY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS_ISO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS2");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MLAYERS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAPS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HOT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LABEL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NAME_ID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SLICING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MANUAL_CONTROL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLLISION");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_234");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_235");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_236");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_237");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_238");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_239");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_240");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_241");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_242");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_243");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_244");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_245");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_246");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_247");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_248");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_249");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_250");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_251");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_252");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_253");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_254");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_255");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MAJOR");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MINOR");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_PATCH");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_LEFT_SIDE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_RIGHT_SIDE");
		return m;
	}

#endif //JS_js_raygui_GUARD