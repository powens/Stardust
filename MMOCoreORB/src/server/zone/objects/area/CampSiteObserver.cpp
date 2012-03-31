/*
 *	server/zone/objects/area/CampSiteObserver.cpp generated by engine3 IDL compiler 0.60
 */

#include "CampSiteObserver.h"

/*
 *	CampSiteObserverStub
 */

enum {RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_ = 6};

CampSiteObserver::CampSiteObserver(CampSiteActiveArea* area) : Observer(DummyConstructorParameter::instance()) {
	CampSiteObserverImplementation* _implementation = new CampSiteObserverImplementation(area);
	_impl = _implementation;
	_impl->_setStub(this);
	_setClassName("CampSiteObserver");
}

CampSiteObserver::CampSiteObserver(DummyConstructorParameter* param) : Observer(param) {
	_setClassName("CampSiteObserver");
}

CampSiteObserver::~CampSiteObserver() {
}



int CampSiteObserver::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	CampSiteObserverImplementation* _implementation = static_cast<CampSiteObserverImplementation*>(_getImplementation());
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_);
		method.addUnsignedIntParameter(eventType);
		method.addObjectParameter(observable);
		method.addObjectParameter(arg1);
		method.addSignedLongParameter(arg2);

		return method.executeWithSignedIntReturn();
	} else
		return _implementation->notifyObserverEvent(eventType, observable, arg1, arg2);
}

DistributedObjectServant* CampSiteObserver::_getImplementation() {

	_updated = true;
	return _impl;
}

void CampSiteObserver::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	CampSiteObserverImplementation
 */

CampSiteObserverImplementation::CampSiteObserverImplementation(DummyConstructorParameter* param) : ObserverImplementation(param) {
	_initializeImplementation();
}


CampSiteObserverImplementation::~CampSiteObserverImplementation() {
}


void CampSiteObserverImplementation::finalize() {
}

void CampSiteObserverImplementation::_initializeImplementation() {
	_setClassHelper(CampSiteObserverHelper::instance());

	_this = NULL;

	_serializationHelperMethod();
}

void CampSiteObserverImplementation::_setStub(DistributedObjectStub* stub) {
	_this = static_cast<CampSiteObserver*>(stub);
	ObserverImplementation::_setStub(stub);
}

DistributedObjectStub* CampSiteObserverImplementation::_getStub() {
	return _this;
}

CampSiteObserverImplementation::operator const CampSiteObserver*() {
	return _this;
}

void CampSiteObserverImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void CampSiteObserverImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void CampSiteObserverImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void CampSiteObserverImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void CampSiteObserverImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void CampSiteObserverImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void CampSiteObserverImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void CampSiteObserverImplementation::_serializationHelperMethod() {
	ObserverImplementation::_serializationHelperMethod();

	_setClassName("CampSiteObserver");

}

void CampSiteObserverImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint32 _varSize = stream->readInt();

		int _currentOffset = stream->getOffset();

		if(CampSiteObserverImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool CampSiteObserverImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (ObserverImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "CampSiteObserver.campArea") {
		TypeInfo<ManagedWeakReference<CampSiteActiveArea* > >::parseFromBinaryStream(&campArea, stream);
		return true;
	}


	return false;
}

void CampSiteObserverImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = CampSiteObserverImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int CampSiteObserverImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	int _count = ObserverImplementation::writeObjectMembers(stream);

	String _name;
	int _offset;
	uint32 _totalSize;
	_name = "CampSiteObserver.campArea";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<ManagedWeakReference<CampSiteActiveArea* > >::toBinaryStream(&campArea, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);


	return _count + 1;
}

CampSiteObserverImplementation::CampSiteObserverImplementation(CampSiteActiveArea* area) {
	_initializeImplementation();
	// server/zone/objects/area/CampSiteObserver.idl():  		campArea = area;
	campArea = area;
	// server/zone/objects/area/CampSiteObserver.idl():  		Logger.setLoggingName("CampSiteObserver");
	Logger::setLoggingName("CampSiteObserver");
}

int CampSiteObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	// server/zone/objects/area/CampSiteObserver.idl():  		if(
	if (campArea != NULL && eventType == ObserverEventType::HEALINGPERFORMED)	// server/zone/objects/area/CampSiteObserver.idl():  			return campArea.notifyHealEvent(arg2);
	return campArea->notifyHealEvent(arg2);
	// server/zone/objects/area/CampSiteObserver.idl():  		return 
	if (campArea != NULL && eventType == ObserverEventType::STARTCOMBAT)	// server/zone/objects/area/CampSiteObserver.idl():  			return campArea.notifyCombatEvent();
	return campArea->notifyCombatEvent();
	// server/zone/objects/area/CampSiteObserver.idl():  		return 1;
	return 1;
}

/*
 *	CampSiteObserverAdapter
 */


#include "engine/orb/messages/InvokeMethodMessage.h"


CampSiteObserverAdapter::CampSiteObserverAdapter(CampSiteObserver* obj) : ObserverAdapter(obj) {
}

void CampSiteObserverAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	DOBMessage* resp = inv->getInvocationMessage();

	switch (methid) {
	case RPC_NOTIFYOBSERVEREVENT__INT_OBSERVABLE_MANAGEDOBJECT_LONG_:
		resp->insertSignedInt(notifyObserverEvent(inv->getUnsignedIntParameter(), static_cast<Observable*>(inv->getObjectParameter()), static_cast<ManagedObject*>(inv->getObjectParameter()), inv->getSignedLongParameter()));
		break;
	default:
		throw Exception("Method does not exists");
	}
}

int CampSiteObserverAdapter::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	return (static_cast<CampSiteObserver*>(stub))->notifyObserverEvent(eventType, observable, arg1, arg2);
}

/*
 *	CampSiteObserverHelper
 */

CampSiteObserverHelper* CampSiteObserverHelper::staticInitializer = CampSiteObserverHelper::instance();

CampSiteObserverHelper::CampSiteObserverHelper() {
	className = "CampSiteObserver";

	Core::getObjectBroker()->registerClass(className, this);
}

void CampSiteObserverHelper::finalizeHelper() {
	CampSiteObserverHelper::finalize();
}

DistributedObject* CampSiteObserverHelper::instantiateObject() {
	return new CampSiteObserver(DummyConstructorParameter::instance());
}

DistributedObjectServant* CampSiteObserverHelper::instantiateServant() {
	return new CampSiteObserverImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* CampSiteObserverHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new CampSiteObserverAdapter(static_cast<CampSiteObserver*>(obj));

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

