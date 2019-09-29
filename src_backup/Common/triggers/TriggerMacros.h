#ifndef _COMMON_TRIGGER_MACROS_H_
#define _COMMON_TRIGGER_MACROS_H_

//#include "Trigger.h"


// https://stackoverflow.com/questions/16683146/can-macros-be-overloaded-by-number-of-arguments

// Necessary macro for Visual C++ to expand macros that use __VA_ARGS__
#define EXPAND(_expr) _expr

#define CAT(_a, _b) _a ## _b
#define SELECT(_name, _num) CAT(_name ## _, _num)

#define GET_COUNT(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, COUNT, ... ) COUNT

// Get the count of the number of passed in arguments.
#define VA_SIZE(...) EXPAND(GET_COUNT("ignored", ##__VA_ARGS__,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))

// Select the overloaded macro from a variadic macro
#define VA_SELECT(_macro, ...) EXPAND(SELECT(_macro, EXPAND(VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

// Line separated values.
#define _PARAM_LINE_LIST(...) \
	EXPAND(VA_SELECT(_PARAM_LINE_LIST, ##__VA_ARGS__))
#define _PARAM_LINE_LIST_1(Ex)
#define _PARAM_LINE_LIST_2(Ex, _t1)
#define _PARAM_LINE_LIST_3(Ex, _t1,_n1)\
	Ex(_t1, _n1)
#define _PARAM_LINE_LIST_5(Ex, _t1,_n1, _t2,_n2)\
	Ex(_t1, _n1) Ex(_t2, _n2)
#define _PARAM_LINE_LIST_7(Ex, _t1,_n1, _t2,_n2, _t3,_n3)\
	Ex(_t1, _n1) Ex(_t2, _n2) Ex(_t3, _n3)
#define _PARAM_LINE_LIST_9(Ex, _t1,_n1, _t2,_n2, _t3,_n3, _t4,_n4)\
	Ex(_t1, _n1) Ex(_t2, _n2) Ex(_t3, _n3) Ex(_t4, _n4) 
#define _PARAM_LINE_LIST_11(Ex, _t1,_n1, _t2,_n2, _t3,_n3, _t4,_n4, _t5,_n5)\
	Ex(_t1, _n1) Ex(_t2, _n2) Ex(_t3, _n3) Ex(_t4, _n4) Ex(_t5, _n5)

// Comma separated values.
#define _PARAM_COMMA_LIST(...) \
	EXPAND(VA_SELECT(_PARAM_COMMA_LIST, ##__VA_ARGS__))
#define _PARAM_COMMA_LIST_1(Ex, _t1,_n1)
#define _PARAM_COMMA_LIST_2(Ex, _t1)
#define _PARAM_COMMA_LIST_3(Ex, _t1,_n1)\
	Ex(_t1, _n1)
#define _PARAM_COMMA_LIST_5(Ex, _t1,_n1, _t2,_n2)\
	Ex(_t1, _n1), Ex(_t2, _n2)
#define _PARAM_COMMA_LIST_7(Ex, _t1,_n1, _t2,_n2, _t3,_n3)\
	Ex(_t1, _n1), Ex(_t2, _n2), Ex(_t3, _n3)
#define _PARAM_COMMA_LIST_9(Ex, _t1,_n1, _t2,_n2, _t3,_n3, _t4,_n4)\
	Ex(_t1, _n1), Ex(_t2, _n2), Ex(_t3, _n3), Ex(_t4, _n4) 
#define _PARAM_COMMA_LIST_11(Ex, _t1,_n1, _t2,_n2, _t3,_n3, _t4,_n4, _t5,_n5)\
	Ex(_t1, _n1), Ex(_t2, _n2), Ex(_t3, _n3), Ex(_t4, _n4), Ex(_t5, _n5)

#define _FUNC_CONSTRUCTOR_PARAMETERS(_type, _name) \
	FunctionOrConstant<_type> _name
#define _FUNC_CONSTRUCTOR_ASSIGNMENTS(_type, _name) \
	m_##_name = _name;\
	m_components.push_back(m_##_name);
#define _FUNC_EXECUTE_PARAMETER_EXECUTE(_type, _name) \
	m_##_name->Execute(context)
#define _FUNC_EXECUTE_PARAMETERS(_type, _name) \
	_type _name
#define _FUNC_MEMBER_VARIABLE(_type, _name) \
	TriggerFunction<_type>* m_##_name;

#define _EVENT_CONSTRUCTOR_PARAMETERS(_type, _name) \
	_type _name
#define _EVENT_CONSTRUCTOR_ASSIGNMENTS(_type, _name) \
	m_##_name = _name;
#define _EVENT_GETTER_FUNCTION(_type, _name) \
	inline Get##_name() { return m_##_name; }
#define _EVENT_MEMBER_VARIABLE(_type, _name) \
	TriggerFunction<_type>* m_##_name;

// TODO: Add a context parameter to Execute (which has pointers to game stuff, and various special trigger variables)
// TODO: Memory management

#define _DECLARE_FUNCTION(_type, _class, _text, _subclass, ...) \
	class _class : public _subclass\
	{\
	public:\
		_class(_PARAM_COMMA_LIST(_FUNC_CONSTRUCTOR_PARAMETERS, ##__VA_ARGS__))\
		{\
			_PARAM_LINE_LIST(_FUNC_CONSTRUCTOR_ASSIGNMENTS, ##__VA_ARGS__);\
			m_text = _text;\
		}\
		inline _type Execute() override\
		{\
			return DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETER_EXECUTE, ##__VA_ARGS__));\
		}\
		_type DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETERS, ##__VA_ARGS__));\
	public:\
		_PARAM_LINE_LIST(_FUNC_MEMBER_VARIABLE, ##__VA_ARGS__)\
	private:\
		_class(_class& copy) {}\
	}

#define _DEFINE_FUNCTION(_type, _class, ...) \
	_type _class::DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETERS, ##__VA_ARGS__))

#define _DECLARE_TRIGGER_EVENT(_class, _event, _text, ...) \
	class _class : public TriggerEvent\
	{\
	public:\
		_class(_PARAM_COMMA_LIST(_FUNC_CONSTRUCTOR_PARAMETERS, ##__VA_ARGS__))\
		{\
			_PARAM_LINE_LIST(_FUNC_CONSTRUCTOR_ASSIGNMENTS, ##__VA_ARGS__);\
			m_text = _text;\
		}\
		inline bool CheckEvent(Context* context, Event* event) override\
		{\
			this->context = context;\
			this->event = (_event*) event;\
			return DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETER_EXECUTE, ##__VA_ARGS__));\
		}\
		inline bool Execute() override\
		{\
			return false;\
		}\
		bool DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETERS, ##__VA_ARGS__));\
	public:\
		_PARAM_LINE_LIST(_FUNC_MEMBER_VARIABLE, ##__VA_ARGS__)\
		_event* event;\
	}

#define _DEFINE_TRIGGER_EVENT(_class, ...) \
	bool _class::DoExecute(_PARAM_COMMA_LIST(_FUNC_EXECUTE_PARAMETERS, ##__VA_ARGS__))


#define _DECLARE_EVENT(_class, _type, ...) \
	class _class : public Event\
	{\
	public:\
		_class(_PARAM_COMMA_LIST(_EVENT_CONSTRUCTOR_PARAMETERS, ##__VA_ARGS__))\
		{\
			m_type = _type;\
			_PARAM_LINE_LIST(_EVENT_CONSTRUCTOR_PARAMETERS, ##__VA_ARGS__)\
		}\
		_PARAM_LINE_LIST(_EVENT_GETTER_FUNCTION, ##__VA_ARGS__)\
	private:\
		_PARAM_LINE_LIST(_EVENT_MEMBER_VARIABLE, ##__VA_ARGS__)\
	}


//-----------------------------------------------------------------------------


#define DECLARE_FUNCTION(_type, _class, _text, ...)	_DECLARE_FUNCTION(_type, _class, _text, TriggerFunction<_type>, ##__VA_ARGS__)
#define DECLARE_EVENT(_class, _event, _text, ...)	_DECLARE_TRIGGER_EVENT(_class, _event, _text, ##__VA_ARGS__)
//#define DECLARE_EVENT(_class, _event, _text, ...)	_DECLARE_FUNCTION(void,  _class, _text, TriggerEvent, ##__VA_ARGS__)
#define DECLARE_CONDITION(_class, _text, ...)		_DECLARE_FUNCTION(bool,  _class, _text, TriggerCondition, ##__VA_ARGS__)
#define DECLARE_ACTION(_class, _text, ...)			_DECLARE_FUNCTION(int,  _class, _text, TriggerAction, ##__VA_ARGS__)

#define DEFINE_FUNCTION(_type, _class, ...)	_DEFINE_FUNCTION(_type, _class, ##__VA_ARGS__)
#define DEFINE_EVENT(_class, _event, ...)	_DEFINE_TRIGGER_EVENT(_class, _event, ##__VA_ARGS__)
//#define DEFINE_EVENT(_class, _event, ...)	_DEFINE_FUNCTION(void, _class, ##__VA_ARGS__)
#define DEFINE_CONDITION(_class, ...)		_DEFINE_FUNCTION(bool, _class, ##__VA_ARGS__)
#define DEFINE_ACTION(_class, ...)			_DEFINE_FUNCTION(int, _class, ##__VA_ARGS__)


//-----------------------------------------------------------------------------


#endif // _COMMON_TRIGGER_MACROS_H_
