// Filename: DistributedType.ipp
namespace bamboo   // open namespace bamboo
{


// null constructor
inline DistributedType::DistributedType() :
    m_subtype(kTypeInvalid), m_size(0)
{
}

// get_subtype returns the type's fundamental type as an integer constant.
inline Subtype DistributedType::get_subtype() const
{
    return m_subtype;
}

// has_fixed_size returns true if the DistributedType has a fixed size in bytes.
inline bool DistributedType::has_fixed_size() const
{
    return (m_size != 0);
}
// get_size returns the size of the DistributedType in bytes or 0 if it is variable.
inline sizetag_t DistributedType::get_size() const
{
    return m_size;
}

// has_alias returns true if this type was defined the an aliased name.
inline bool DistributedType::has_alias() const
{
    return (m_alias.length() > 0);
}
// get_alias returns the name used to define the type, or the empty string.
inline const std::string& DistributedType::get_alias() const
{
    return m_alias;
}

// set_alias gives this type the alternate name <alias>.
inline void DistributedType::set_alias(const std::string& alias)
{
	m_alias = alias;
}

} // close namespace bamboo
