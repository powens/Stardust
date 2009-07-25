/*
 *	server/zone/objects/player/PlayerObject.cpp generated by engine3 IDL compiler 0.60
 */

#include "PlayerObject.h"

#include "server/zone/ZoneClientSession.h"

/*
 *	PlayerObjectStub
 */

PlayerObject::PlayerObject(LuaObject* templateData) : IntangibleObject(DummyConstructorParameter::instance()) {
	_impl = new PlayerObjectImplementation(templateData);
	_impl->_setStub(this);

	((PlayerObjectImplementation*) _impl)->_serializationHelperMethod();
}

PlayerObject::PlayerObject(DummyConstructorParameter* param) : IntangibleObject(param) {
}

PlayerObject::~PlayerObject() {
}

CreatureObject* PlayerObject::getCreatureObject() {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		return (CreatureObject*) method.executeWithObjectReturn();
	} else
		return ((PlayerObjectImplementation*) _impl)->getCreatureObject();
}

void PlayerObject::setCreatureObject(CreatureObject* object) {
	if (_impl == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		((PlayerObjectImplementation*) _impl)->setCreatureObject(object);
}

/*
 *	PlayerObjectImplementation
 */

PlayerObjectImplementation::~PlayerObjectImplementation() {
}

void PlayerObjectImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (PlayerObject*) stub;
	IntangibleObjectImplementation::_setStub(stub);
}

DistributedObjectStub* PlayerObjectImplementation::_getStub() {
	return _this;
}

PlayerObjectImplementation::operator const PlayerObject*() {
	return _this;
}

void PlayerObjectImplementation::_serializationHelperMethod() {
	IntangibleObjectImplementation::_serializationHelperMethod();

	addSerializableVariable("creatureObject", creatureObject);
	addSerializableVariable("owner", owner);
}

CreatureObject* PlayerObjectImplementation::getCreatureObject() {
	// server/zone/objects/player/PlayerObject.idl(62):  return creatureObject;
	return creatureObject;
}

void PlayerObjectImplementation::setCreatureObject(CreatureObject* object) {
	// server/zone/objects/player/PlayerObject.idl(66):  creatureObject = object;
	creatureObject = object;
}

/*
 *	PlayerObjectAdapter
 */

PlayerObjectAdapter::PlayerObjectAdapter(PlayerObjectImplementation* obj) : IntangibleObjectAdapter(obj) {
}

Packet* PlayerObjectAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case 6:
		resp->insertLong(getCreatureObject()->_getObjectID());
		break;
	case 7:
		setCreatureObject((CreatureObject*) inv->getObjectParameter());
		break;
	default:
		return NULL;
	}

	return resp;
}

CreatureObject* PlayerObjectAdapter::getCreatureObject() {
	return ((PlayerObjectImplementation*) impl)->getCreatureObject();
}

void PlayerObjectAdapter::setCreatureObject(CreatureObject* object) {
	return ((PlayerObjectImplementation*) impl)->setCreatureObject(object);
}

/*
 *	PlayerObjectHelper
 */

PlayerObjectHelper* PlayerObjectHelper::staticInitializer = PlayerObjectHelper::instance();

PlayerObjectHelper::PlayerObjectHelper() {
	className = "PlayerObject";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void PlayerObjectHelper::finalizeHelper() {
	PlayerObjectHelper::finalize();
}

DistributedObject* PlayerObjectHelper::instantiateObject() {
	return new PlayerObject(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* PlayerObjectHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new PlayerObjectAdapter((PlayerObjectImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

