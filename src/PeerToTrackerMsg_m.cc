//
// Generated file, do not edit! Created by opp_msgc 4.3 from PeerToTrackerMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "PeerToTrackerMsg_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("P2T_MSG_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("P2T_MSG_TYPE"));
    e->insert(P2T_REGISTRATION_REQUEST, "P2T_REGISTRATION_REQUEST");
    e->insert(P2T_REFRESH_MESSAGE, "P2T_REFRESH_MESSAGE");
    e->insert(T2P_MEMBERSHIP_RESPONSE, "T2P_MEMBERSHIP_RESPONSE");
    e->insert(P2T_LEAVE_MESSAGE, "P2T_LEAVE_MESSAGE");
    e->insert(PTT_DOWNLOAD_COMPLETE, "PTT_DOWNLOAD_COMPLETE");
);

Register_Class(P2T_Packet);

P2T_Packet::P2T_Packet(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
}

P2T_Packet::P2T_Packet(const P2T_Packet& other) : cPacket(other)
{
    copy(other);
}

P2T_Packet::~P2T_Packet()
{
}

P2T_Packet& P2T_Packet::operator=(const P2T_Packet& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void P2T_Packet::copy(const P2T_Packet& other)
{
    this->type_var = other.type_var;
}

void P2T_Packet::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void P2T_Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int P2T_Packet::getType() const
{
    return type_var;
}

void P2T_Packet::setType(int type)
{
    this->type_var = type;
}

class P2T_PacketDescriptor : public cClassDescriptor
{
  public:
    P2T_PacketDescriptor();
    virtual ~P2T_PacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(P2T_PacketDescriptor);

P2T_PacketDescriptor::P2T_PacketDescriptor() : cClassDescriptor("P2T_Packet", "cPacket")
{
}

P2T_PacketDescriptor::~P2T_PacketDescriptor()
{
}

bool P2T_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2T_Packet *>(obj)!=NULL;
}

const char *P2T_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2T_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int P2T_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *P2T_PacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int P2T_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2T_PacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *P2T_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "P2T_MSG_TYPE";
            return NULL;
        default: return NULL;
    }
}

int P2T_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2T_Packet *pp = (P2T_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2T_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_Packet *pp = (P2T_Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool P2T_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2T_Packet *pp = (P2T_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *P2T_PacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *P2T_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_Packet *pp = (P2T_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Ownership_Message);

Ownership_Message::Ownership_Message(const char *name, int kind) : P2T_Packet(name,kind)
{
    this->id_var = 0;
    owned_chunks_arraysize = 0;
    this->owned_chunks_var = 0;
}

Ownership_Message::Ownership_Message(const Ownership_Message& other) : P2T_Packet(other)
{
    owned_chunks_arraysize = 0;
    this->owned_chunks_var = 0;
    copy(other);
}

Ownership_Message::~Ownership_Message()
{
    delete [] owned_chunks_var;
}

Ownership_Message& Ownership_Message::operator=(const Ownership_Message& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void Ownership_Message::copy(const Ownership_Message& other)
{
    this->id_var = other.id_var;
    delete [] this->owned_chunks_var;
    this->owned_chunks_var = (other.owned_chunks_arraysize==0) ? NULL : new int[other.owned_chunks_arraysize];
    owned_chunks_arraysize = other.owned_chunks_arraysize;
    for (unsigned int i=0; i<owned_chunks_arraysize; i++)
        this->owned_chunks_var[i] = other.owned_chunks_var[i];
}

void Ownership_Message::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    b->pack(owned_chunks_arraysize);
    doPacking(b,this->owned_chunks_var,owned_chunks_arraysize);
}

void Ownership_Message::parsimUnpack(cCommBuffer *b)
{
    P2T_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    delete [] this->owned_chunks_var;
    b->unpack(owned_chunks_arraysize);
    if (owned_chunks_arraysize==0) {
        this->owned_chunks_var = 0;
    } else {
        this->owned_chunks_var = new int[owned_chunks_arraysize];
        doUnpacking(b,this->owned_chunks_var,owned_chunks_arraysize);
    }
}

const char * Ownership_Message::getId() const
{
    return id_var.c_str();
}

void Ownership_Message::setId(const char * id)
{
    this->id_var = id;
}

void Ownership_Message::setOwned_chunksArraySize(unsigned int size)
{
    int *owned_chunks_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = owned_chunks_arraysize < size ? owned_chunks_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        owned_chunks_var2[i] = this->owned_chunks_var[i];
    for (unsigned int i=sz; i<size; i++)
        owned_chunks_var2[i] = 0;
    owned_chunks_arraysize = size;
    delete [] this->owned_chunks_var;
    this->owned_chunks_var = owned_chunks_var2;
}

unsigned int Ownership_Message::getOwned_chunksArraySize() const
{
    return owned_chunks_arraysize;
}

int Ownership_Message::getOwned_chunks(unsigned int k) const
{
    if (k>=owned_chunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", owned_chunks_arraysize, k);
    return owned_chunks_var[k];
}

void Ownership_Message::setOwned_chunks(unsigned int k, int owned_chunks)
{
    if (k>=owned_chunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", owned_chunks_arraysize, k);
    this->owned_chunks_var[k] = owned_chunks;
}

class Ownership_MessageDescriptor : public cClassDescriptor
{
  public:
    Ownership_MessageDescriptor();
    virtual ~Ownership_MessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(Ownership_MessageDescriptor);

Ownership_MessageDescriptor::Ownership_MessageDescriptor() : cClassDescriptor("Ownership_Message", "P2T_Packet")
{
}

Ownership_MessageDescriptor::~Ownership_MessageDescriptor()
{
}

bool Ownership_MessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Ownership_Message *>(obj)!=NULL;
}

const char *Ownership_MessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Ownership_MessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int Ownership_MessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *Ownership_MessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "owned_chunks",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int Ownership_MessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "owned_chunks")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Ownership_MessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *Ownership_MessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int Ownership_MessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Ownership_Message *pp = (Ownership_Message *)object; (void)pp;
    switch (field) {
        case 1: return pp->getOwned_chunksArraySize();
        default: return 0;
    }
}

std::string Ownership_MessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Ownership_Message *pp = (Ownership_Message *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return long2string(pp->getOwned_chunks(i));
        default: return "";
    }
}

bool Ownership_MessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Ownership_Message *pp = (Ownership_Message *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setOwned_chunks(i,string2long(value)); return true;
        default: return false;
    }
}

const char *Ownership_MessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *Ownership_MessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Ownership_Message *pp = (Ownership_Message *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(T2P_MEMBERSHIP_Res);

T2P_MEMBERSHIP_Res::T2P_MEMBERSHIP_Res(const char *name, int kind) : P2T_Packet(name,kind)
{
    ids_arraysize = 0;
    this->ids_var = 0;
    peer_to_chunk_ownership_arraysize = 0;
    this->peer_to_chunk_ownership_var = 0;
}

T2P_MEMBERSHIP_Res::T2P_MEMBERSHIP_Res(const T2P_MEMBERSHIP_Res& other) : P2T_Packet(other)
{
    ids_arraysize = 0;
    this->ids_var = 0;
    peer_to_chunk_ownership_arraysize = 0;
    this->peer_to_chunk_ownership_var = 0;
    copy(other);
}

T2P_MEMBERSHIP_Res::~T2P_MEMBERSHIP_Res()
{
    delete [] ids_var;
    for (unsigned int i=0; i<peer_to_chunk_ownership_arraysize; i++)
        drop(&(this->peer_to_chunk_ownership_var[i]));
    delete [] peer_to_chunk_ownership_var;
}

T2P_MEMBERSHIP_Res& T2P_MEMBERSHIP_Res::operator=(const T2P_MEMBERSHIP_Res& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void T2P_MEMBERSHIP_Res::copy(const T2P_MEMBERSHIP_Res& other)
{
    delete [] this->ids_var;
    this->ids_var = (other.ids_arraysize==0) ? NULL : new opp_string[other.ids_arraysize];
    ids_arraysize = other.ids_arraysize;
    for (unsigned int i=0; i<ids_arraysize; i++)
        this->ids_var[i] = other.ids_var[i];
    delete [] this->peer_to_chunk_ownership_var;
    this->peer_to_chunk_ownership_var = (other.peer_to_chunk_ownership_arraysize==0) ? NULL : new Ownership_Message[other.peer_to_chunk_ownership_arraysize];
    peer_to_chunk_ownership_arraysize = other.peer_to_chunk_ownership_arraysize;
    for (unsigned int i=0; i<peer_to_chunk_ownership_arraysize; i++)
    {
        take(&(this->peer_to_chunk_ownership_var[i]));
        this->peer_to_chunk_ownership_var[i] = other.peer_to_chunk_ownership_var[i];
        this->peer_to_chunk_ownership_var[i].setName(other.peer_to_chunk_ownership_var[i].getName());
    }
}

void T2P_MEMBERSHIP_Res::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    b->pack(ids_arraysize);
    doPacking(b,this->ids_var,ids_arraysize);
    b->pack(peer_to_chunk_ownership_arraysize);
    doPacking(b,this->peer_to_chunk_ownership_var,peer_to_chunk_ownership_arraysize);
}

void T2P_MEMBERSHIP_Res::parsimUnpack(cCommBuffer *b)
{
    P2T_Packet::parsimUnpack(b);
    delete [] this->ids_var;
    b->unpack(ids_arraysize);
    if (ids_arraysize==0) {
        this->ids_var = 0;
    } else {
        this->ids_var = new opp_string[ids_arraysize];
        doUnpacking(b,this->ids_var,ids_arraysize);
    }
    delete [] this->peer_to_chunk_ownership_var;
    b->unpack(peer_to_chunk_ownership_arraysize);
    if (peer_to_chunk_ownership_arraysize==0) {
        this->peer_to_chunk_ownership_var = 0;
    } else {
        this->peer_to_chunk_ownership_var = new Ownership_Message[peer_to_chunk_ownership_arraysize];
        doUnpacking(b,this->peer_to_chunk_ownership_var,peer_to_chunk_ownership_arraysize);
    }
}

void T2P_MEMBERSHIP_Res::setIdsArraySize(unsigned int size)
{
    opp_string *ids_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = ids_arraysize < size ? ids_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ids_var2[i] = this->ids_var[i];
    for (unsigned int i=sz; i<size; i++)
        ids_var2[i] = 0;
    ids_arraysize = size;
    delete [] this->ids_var;
    this->ids_var = ids_var2;
}

unsigned int T2P_MEMBERSHIP_Res::getIdsArraySize() const
{
    return ids_arraysize;
}

const char * T2P_MEMBERSHIP_Res::getIds(unsigned int k) const
{
    if (k>=ids_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ids_arraysize, k);
    return ids_var[k].c_str();
}

void T2P_MEMBERSHIP_Res::setIds(unsigned int k, const char * ids)
{
    if (k>=ids_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ids_arraysize, k);
    this->ids_var[k] = ids;
}

void T2P_MEMBERSHIP_Res::setPeer_to_chunk_ownershipArraySize(unsigned int size)
{
    Ownership_Message *peer_to_chunk_ownership_var2 = (size==0) ? NULL : new Ownership_Message[size];
    unsigned int sz = peer_to_chunk_ownership_arraysize < size ? peer_to_chunk_ownership_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        peer_to_chunk_ownership_var2[i] = this->peer_to_chunk_ownership_var[i];
    for (unsigned int i=sz; i<size; i++)
        take(&(peer_to_chunk_ownership_var2[i]));
    peer_to_chunk_ownership_arraysize = size;
    delete [] this->peer_to_chunk_ownership_var;
    this->peer_to_chunk_ownership_var = peer_to_chunk_ownership_var2;
}

unsigned int T2P_MEMBERSHIP_Res::getPeer_to_chunk_ownershipArraySize() const
{
    return peer_to_chunk_ownership_arraysize;
}

Ownership_Message& T2P_MEMBERSHIP_Res::getPeer_to_chunk_ownership(unsigned int k)
{
    if (k>=peer_to_chunk_ownership_arraysize) throw cRuntimeError("Array of size %d indexed by %d", peer_to_chunk_ownership_arraysize, k);
    return peer_to_chunk_ownership_var[k];
}

void T2P_MEMBERSHIP_Res::setPeer_to_chunk_ownership(unsigned int k, const Ownership_Message& peer_to_chunk_ownership)
{
    if (k>=peer_to_chunk_ownership_arraysize) throw cRuntimeError("Array of size %d indexed by %d", peer_to_chunk_ownership_arraysize, k);
    this->peer_to_chunk_ownership_var[k] = peer_to_chunk_ownership;
}

class T2P_MEMBERSHIP_ResDescriptor : public cClassDescriptor
{
  public:
    T2P_MEMBERSHIP_ResDescriptor();
    virtual ~T2P_MEMBERSHIP_ResDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(T2P_MEMBERSHIP_ResDescriptor);

T2P_MEMBERSHIP_ResDescriptor::T2P_MEMBERSHIP_ResDescriptor() : cClassDescriptor("T2P_MEMBERSHIP_Res", "P2T_Packet")
{
}

T2P_MEMBERSHIP_ResDescriptor::~T2P_MEMBERSHIP_ResDescriptor()
{
}

bool T2P_MEMBERSHIP_ResDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<T2P_MEMBERSHIP_Res *>(obj)!=NULL;
}

const char *T2P_MEMBERSHIP_ResDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int T2P_MEMBERSHIP_ResDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int T2P_MEMBERSHIP_ResDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *T2P_MEMBERSHIP_ResDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ids",
        "peer_to_chunk_ownership",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int T2P_MEMBERSHIP_ResDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "ids")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "peer_to_chunk_ownership")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *T2P_MEMBERSHIP_ResDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "Ownership_Message",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *T2P_MEMBERSHIP_ResDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int T2P_MEMBERSHIP_ResDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBERSHIP_Res *pp = (T2P_MEMBERSHIP_Res *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIdsArraySize();
        case 1: return pp->getPeer_to_chunk_ownershipArraySize();
        default: return 0;
    }
}

std::string T2P_MEMBERSHIP_ResDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBERSHIP_Res *pp = (T2P_MEMBERSHIP_Res *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getIds(i));
        case 1: {std::stringstream out; out << pp->getPeer_to_chunk_ownership(i); return out.str();}
        default: return "";
    }
}

bool T2P_MEMBERSHIP_ResDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBERSHIP_Res *pp = (T2P_MEMBERSHIP_Res *)object; (void)pp;
    switch (field) {
        case 0: pp->setIds(i,(value)); return true;
        default: return false;
    }
}

const char *T2P_MEMBERSHIP_ResDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "Ownership_Message",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *T2P_MEMBERSHIP_ResDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBERSHIP_Res *pp = (T2P_MEMBERSHIP_Res *)object; (void)pp;
    switch (field) {
        case 1: return (void *)static_cast<cObject *>(&pp->getPeer_to_chunk_ownership(i)); break;
        default: return NULL;
    }
}

Register_Class(P2T_LEAVE_Msg);

P2T_LEAVE_Msg::P2T_LEAVE_Msg(const char *name, int kind) : P2T_Packet(name,kind)
{
    this->id_var = 0;
}

P2T_LEAVE_Msg::P2T_LEAVE_Msg(const P2T_LEAVE_Msg& other) : P2T_Packet(other)
{
    copy(other);
}

P2T_LEAVE_Msg::~P2T_LEAVE_Msg()
{
}

P2T_LEAVE_Msg& P2T_LEAVE_Msg::operator=(const P2T_LEAVE_Msg& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void P2T_LEAVE_Msg::copy(const P2T_LEAVE_Msg& other)
{
    this->id_var = other.id_var;
}

void P2T_LEAVE_Msg::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    doPacking(b,this->id_var);
}

void P2T_LEAVE_Msg::parsimUnpack(cCommBuffer *b)
{
    P2T_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
}

const char * P2T_LEAVE_Msg::getId() const
{
    return id_var.c_str();
}

void P2T_LEAVE_Msg::setId(const char * id)
{
    this->id_var = id;
}

class P2T_LEAVE_MsgDescriptor : public cClassDescriptor
{
  public:
    P2T_LEAVE_MsgDescriptor();
    virtual ~P2T_LEAVE_MsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(P2T_LEAVE_MsgDescriptor);

P2T_LEAVE_MsgDescriptor::P2T_LEAVE_MsgDescriptor() : cClassDescriptor("P2T_LEAVE_Msg", "P2T_Packet")
{
}

P2T_LEAVE_MsgDescriptor::~P2T_LEAVE_MsgDescriptor()
{
}

bool P2T_LEAVE_MsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2T_LEAVE_Msg *>(obj)!=NULL;
}

const char *P2T_LEAVE_MsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2T_LEAVE_MsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int P2T_LEAVE_MsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *P2T_LEAVE_MsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int P2T_LEAVE_MsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2T_LEAVE_MsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *P2T_LEAVE_MsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int P2T_LEAVE_MsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2T_LEAVE_Msg *pp = (P2T_LEAVE_Msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2T_LEAVE_MsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_LEAVE_Msg *pp = (P2T_LEAVE_Msg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        default: return "";
    }
}

bool P2T_LEAVE_MsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2T_LEAVE_Msg *pp = (P2T_LEAVE_Msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        default: return false;
    }
}

const char *P2T_LEAVE_MsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *P2T_LEAVE_MsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_LEAVE_Msg *pp = (P2T_LEAVE_Msg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


