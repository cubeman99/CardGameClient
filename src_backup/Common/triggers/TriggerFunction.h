#ifndef _COMMON_TRIGGER_FUNCTION_H_
#define _COMMON_TRIGGER_FUNCTION_H_

#include "TriggerComponent.h"
#include <sstream>


template <typename T_Type>
class TriggerFunction : public TriggerComponent
{
public:
	typedef T_Type type;

public:
	inline T_Type Execute(Context* context)
	{
		this->context = context;
		return Execute();
	}

	inline const std::string& GetClassName() const { return m_className; }
	inline const std::string& GetTypeName() const { return m_typeName; }

protected:
	std::string m_className;
	std::string m_typeName;

private:
	virtual T_Type Execute() = 0;
};


template <typename T_Type>
class TriggerFunctionConstant : public TriggerFunction<T_Type>
{
public:
	TriggerFunctionConstant(T_Type value) :
		m_value(value)
	{
		std::stringstream ss;
		ss << value;
		m_text = ss.str();
	}

	T_Type Execute() override
	{
		return m_value;
	}

private:
	T_Type m_value;
};


template <typename T_Type>
class FunctionOrConstant
{
public:
	typedef T_Type type;
public:
	FunctionOrConstant(TriggerFunction<T_Type>* function) :
		m_function(function)
	{
	}

	FunctionOrConstant(T_Type constant)
	{
		m_function = new TriggerFunctionConstant<T_Type>(constant);
	}

	// Cast back into a TriggerFunction pointer.
	operator TriggerFunction<T_Type>*()
	{
		return m_function;
	}

protected:
	TriggerFunction<T_Type>* m_function;
};


#endif // _COMMON_TRIGGER_FUNCTION_H_