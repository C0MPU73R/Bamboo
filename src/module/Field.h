// Filename: Field.h
#pragma once
#include "module/KeywordList.h"
#include "values/Value.h"
namespace bamboo { // open namespace

// Foward declarations
class DistributedType;
class Module;
class Class;
class Struct;
class MolecularField;
class HashGenerator;

// A Field is a member of a class or struct.
class Field : public KeywordList {
  public:
    Field(DistributedType *type, const std::string& name = "");
    virtual ~Field();

    // as_molecular returns this as a MolecularField if it is molecular, or nullptr otherwise.
    virtual MolecularField *as_molecular();
    virtual const MolecularField *as_molecular() const;

    // get_id returns a unique index number associated with this field.
    inline unsigned int get_id() const;
    // get_name returns the field's name.  An unnamed field returns the empty string.
    inline const std::string& get_name() const;
    // get_type returns the DistributedType of the field.
    inline DistributedType *get_type();
    inline const DistributedType *get_type() const;
    // get_struct returns the Struct that contains this field.
    inline Struct *get_struct();
    inline const Struct *get_struct() const;

    // has_default_value returns true if a default value was defined for this field.
    inline bool has_default_value() const;
    // get_default_value returns the default value for this field.
    //     If a default value hasn't been set, returns an implicit default.
    inline const Value get_default_value() const;

    // set_name sets the name of this field.  Returns false if a field with
    //     the same name already exists in the containing struct.
    bool set_name(const std::string& name);

    // set_type sets the distributed type of the field and clear's the default value.
    void set_type(DistributedType *type);

    // set_default_value defines a default value for this field.
    //     Returns false if the value is invalid for the field's type.
    virtual bool set_default_value(const Value default_value);
    virtual bool set_default_value(const std::vector<uint8_t>& default_value);

  protected:
    // set_id sets the unique index number associated with the field.
    void set_id(unsigned int id);
    friend class Module;

    // set_struct sets a pointer to the struct containing the field.
    void set_struct(Struct *strct);
    friend class Struct;
    friend class Class;

    Struct *m_struct;
    unsigned int m_id;
    std::string m_name;
    DistributedType *m_type;

    bool m_has_default_value; // is true if an explicity default has been set
    Value m_default_value; // the binary data of the default value encoded in a string
};


} // close namespace bamboo
#include "Field.ipp"
