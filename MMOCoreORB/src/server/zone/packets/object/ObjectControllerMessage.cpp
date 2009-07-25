/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 2 of the License,
 or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for
 more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

 Linking Engine3 statically or dynamically with other modules
 is making a combined work based on Engine3.
 Thus, the terms and conditions of the GNU Lesser General Public License
 cover the whole combination.

 In addition, as a special exception, the copyright holders of Engine3
 give you permission to combine Engine3 program with free software
 programs or libraries that are released under the GNU LGPL and with
 code included in the standard release of Core3 under the GNU LGPL
 license (or modified versions of such code, with unchanged license).
 You may copy and distribute such a system following the terms of the
 GNU LGPL for Engine3 and the licenses of the other code concerned,
 provided that you include the source code of that other code when
 and as the GNU LGPL requires distribution of source code.

 Note that people who make modified versions of Engine3 are not obligated
 to grant this special exception for their modified versions;
 it is their choice whether to do so. The GNU Lesser General Public License
 gives permission to release a modified version without this exception;
 this exception also makes it possible to release a modified version
 which carries forward this exception.
 */

#include "ObjectControllerMessage.h"

ObjectFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* ObjectControllerMessageCallback::objectMessageControllerFactory = NULL;

ObjectControllerMessage::ObjectControllerMessage(uint64 objid, uint32 header1,
		uint32 header2, bool comp) :
	BaseMessage() {
	insertShort(0x05);
	insertInt(0x80CE5E46); // CRC
	insertInt(header1);
	insertInt(header2);
	insertLong(objid);
	insertInt(0x00);

	setCompression(comp);
}

void ObjectControllerMessageCallback::parse(Message* message) {
	priority = message->parseInt();
	type = message->parseInt();

	objectID = message->parseLong();

	objectControllerCallback = objectMessageControllerFactory->createObject(type, this);

	if (objectControllerCallback == NULL) {
		StringBuffer msg;
		msg << "unregistered 0x" << hex << type << " object controller message received\n";

		SceneObject* player = client->getPlayer();
		player->error(msg.toString());
		return;
	}

	try {

		objectControllerCallback->parse(message);

	} catch (Exception& e) {
		System::out << "exception parsing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();
	} catch (...) {
		System::out << "unknown exception caught in ObjectControllerMessageCallback::parse";
	}

}

void ObjectControllerMessageCallback::execute() {
	SceneObject* player = client->getPlayer();

	if (player == NULL)
		return;

	try {
		player->wlock();


		if (objectID != player->getObjectID()) {
			player->error("wrong object id in object controller message?");
			player->unlock();

			return;
		}

		if (objectControllerCallback != NULL)
			objectControllerCallback->execute();

		player->unlock();

	} catch (Exception& e) {
		player->unlock();

		System::out << "exception executing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();
	} catch (...) {
		player->unlock();

		System::out << "unknown exception caught in ObjectControllerMessageCallback::execute";
	}
}

