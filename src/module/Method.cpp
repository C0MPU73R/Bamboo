// Filename: Method.cpp
#include "Method.h"
#include "../module/Parameter.h"
#include "../module/Struct.h"
using namespace std;
namespace bamboo
{


Method::Method()
{
    m_subtype = Subtype_Method;
}

Method *Method::as_method()
{
    return this;
}

const Method *Method::as_method() const
{
    return this;
}

Parameter *Method::add_param(const std::string& name, Type *type, bool param_owns_type)
{
    // Parameters can't have method types for now
    if(type->subtype() == Subtype_Method) {
        return nullptr;
    }

    // Parameters can't have class types for now
    if(type->subtype() == Subtype_Struct && type->as_struct()->as_class()) {
        return nullptr;
    }

    // Parameters must have unique names
    if(m_params_by_name.find(name) != m_params_by_name.end()) {
        return nullptr;
    }

    unsigned int pos = (unsigned int)m_params.size();
    Parameter *param = new Parameter(name, type, param_owns_type);

    if(!name.empty()) {
        m_params_by_name.emplace(name, param);
        m_positions_by_name.emplace(name, pos);
    }

    // Update our size
    if(has_fixed_size() || m_params.size() == 1) {
        if(param->type()->has_fixed_size()) {
            m_size += param->type()->fixed_size();
        } else {
            m_size = 0;
        }
    }

    // Transfer ownership of the Parameter to the Method
    param->m_method = this;
    param->m_position = pos;
    m_params.push_back(unique_ptr<Parameter>(param));

    return param;
}

bool Method::add_param(Parameter *param)
{
    // Parameters must have unique names
    if(!param->name().empty()) {
        bool inserted = m_params_by_name.emplace(param->name(), param).second;
        if(!inserted) { return false; }
        m_positions_by_name[param->name()] = (unsigned int) m_params.size();
    }

    // Update our size
    if(has_fixed_size() || m_params.size() == 1) {
        if(param->type()->has_fixed_size()) {
            m_size += param->type()->fixed_size();
        } else {
            m_size = 0;
        }
    }

    // Transfer ownership of the Parameter to the Method
    param->m_method = this;
    param->m_position = (unsigned int)m_params.size();
    m_params.push_back(unique_ptr<Parameter>(param));

    return true;
}

void Method::update_param_type(Parameter *, Type *new_type, Type *old_type)
{
    if(new_type->has_fixed_size()) {
        if(old_type != nullptr && old_type->has_fixed_size()) {
            m_size -= old_type->fixed_size();
            m_size += old_type->fixed_size();
        } else {
            size_t fixed_size = 0;
            bool is_fixed_size = true;
            for(unique_ptr<Parameter>& param_ptr : m_params) {
                if(!param_ptr->type()->has_fixed_size()) {
                    is_fixed_size = false;
                    break;
                } else {
                    fixed_size += param_ptr->type()->fixed_size();
                }
            }

            if(is_fixed_size) {
                m_size = fixed_size;
            }
        }
    } else {
        m_size = 0;
    }
}



} // close namespace bamboo
