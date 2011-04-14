/*
    This file is part of Mitsuba, a physically based rendering system.

    Copyright (c) 2007-2011 by Wenzel Jakob and others.

    Mitsuba is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Mitsuba is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "shapegroup.h"

MTS_NAMESPACE_BEGIN

/**
 * \brief Geometry instancing support (to be used in conjunction
 * with the \c shapegroup plugin)
 */
class Instance : public Shape {
public:
	/// Create a new instance based on properties from an XML file
	Instance(const Properties &props);

	/// Unserialize from a binary data stream
	Instance(Stream *stream, InstanceManager *manager);

	/// Serialize to a binary data stream
	void serialize(Stream *stream, InstanceManager *manager) const;

	/** \brief Configure this object (called _once_ after construction
	   and addition of all child ConfigurableObjects.) */
	void configure();

	/// Return the object-to-world transformation used by this instance
	inline Transform getWorldTransform() const { return m_objectToWorld; }

	/// Add a child ConfigurableObject
	void addChild(const std::string &name, ConfigurableObject *child);
	
	/// Return a pointer to the associated \ref ShapeGroup
	inline ShapeGroup* getShapeGroup() { return m_shapeGroup; }

	/// Return a pointer to the associated \ref ShapeGroup (const version)
	inline const ShapeGroup* getShapeGroup() const { return m_shapeGroup.get(); }
	
	// =============================================================
	//! @{ \name Implementation of the Shape interface
	// =============================================================

	AABB getAABB() const;

	Float getSurfaceArea() const;

	bool rayIntersect(const Ray &_ray, Float mint, 
			Float maxt, Float &t, void *temp) const;

	bool rayIntersect(const Ray &_ray, Float mint, Float maxt) const;

	void fillIntersectionRecord(const Ray &ray, 
		const void *temp, Intersection &its) const;
	
	
	//! @}
	// =============================================================

	MTS_DECLARE_CLASS()
private:
	ref<ShapeGroup> m_shapeGroup;
	Transform m_objectToWorld, m_worldToObject;
};

MTS_NAMESPACE_END
