//
// Generated file, do not edit! Created by opp_msgc 4.3 from PeerToPeerMSG.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "PeerToPeerMSG_m.h"

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
    cEnum *e = cEnum::find("P2P_MSG_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("P2P_MSG_TYPE"));
    e->insert(P2P_REQUEST, "P2P_REQUEST");
    e->insert(P2P_RESPONSE, "P2P_RESPONSE");
);

Register_Class(P2P_Packet);

P2P_Packet::P2P_Packet(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
}

P2P_Packet::P2P_Packet(const P2P_Packet& other) : cPacket(other)
{
    copy(other);
}

P2P_Packet::~P2P_Packet()
{
}

P2P_Packet& P2P_Packet::operator=(const P2P_Packet& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void P2P_Packet::copy(const P2P_Packet& other)
{
    this->type_var = other.type_var;
}

void P2P_Packet::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void P2P_Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int P2P_Packet::getType() const
{
    return type_var;
}

void P2P_Packet::setType(int type)
{
    this->type_var = type;
}

class P2P_PacketDescriptor : public cClassDescriptor
{
  public:
    P2P_PacketDescriptor();
    virtual ~P2P_PacketDescriptor();

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

Register_ClassDescriptor(P2P_PacketDescriptor);

P2P_PacketDescriptor::P2P_PacketDescriptor() : cClassDescriptor("P2P_Packet", "cPacket")
{
}

P2P_PacketDescriptor::~P2P_PacketDescriptor()
{
}

bool P2P_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2P_Packet *>(obj)!=NULL;
}

const char *P2P_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2P_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int P2P_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *P2P_PacketDescriptor::getFieldName(void *object, int field) const
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

int P2P_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2P_PacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *P2P_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "P2P_MSG_TYPE";
            return NULL;
        default: return NULL;
    }
}

int P2P_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Packet *pp = (P2P_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2P_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Packet *pp = (P2P_Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool P2P_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Packet *pp = (P2P_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *P2P_PacketDescriptor::getFieldStructName(void *object, int field) const
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

void *P2P_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Packet *pp = (P2P_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(P2P_Req);

P2P_Req::P2P_Req(const char *name, int kind) : P2P_Packet(name,kind)
{
    this->id_var = 0;
    this->chunkNo_var = 0;
}

P2P_Req::P2P_Req(const P2P_Req& other) : P2P_Packet(other)
{
    copy(other);
}

P2P_Req::~P2P_Req()
{
}

P2P_Req& P2P_Req::operator=(const P2P_Req& other)
{
    if (this==&other) return *this;
    P2P_Packet::operator=(other);
    copy(other);
    return *this;
}

void P2P_Req::copy(const P2P_Req& other)
{
    this->id_var = other.id_var;
    this->chunkNo_var = other.chunkNo_var;
}

void P2P_Req::parsimPack(cCommBuffer *b)
{
    P2P_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    doPacking(b,this->chunkNo_var);
}

void P2P_Req::parsimUnpack(cCommBuffer *b)
{
    P2P_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->chunkNo_var);
}

const char * P2P_Req::getId() const
{
    return id_var.c_str();
}

void P2P_Req::setId(const char * id)
{
    this->id_var = id;
}

int P2P_Req::getChunkNo() const
{
    return chunkNo_var;
}

void P2P_Req::setChunkNo(int chunkNo)
{
    this->chunkNo_var = chunkNo;
}

class P2P_ReqDescriptor : public cClassDescriptor
{
  public:
    P2P_ReqDescriptor();
    virtual ~P2P_ReqDescriptor();

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

Register_ClassDescriptor(P2P_ReqDescriptor);

P2P_ReqDescriptor::P2P_ReqDescriptor() : cClassDescriptor("P2P_Req", "P2P_Packet")
{
}

P2P_ReqDescriptor::~P2P_ReqDescriptor()
{
}

bool P2P_ReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2P_Req *>(obj)!=NULL;
}

const char *P2P_ReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2P_ReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int P2P_ReqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *P2P_ReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "chunkNo",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int P2P_ReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunkNo")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2P_ReqDescriptor::getFieldTypeString(void *object, int field) const
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

const char *P2P_ReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int P2P_ReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Req *pp = (P2P_Req *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2P_ReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Req *pp = (P2P_Req *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return long2string(pp->getChunkNo());
        default: return "";
    }
}

bool P2P_ReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Req *pp = (P2P_Req *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setChunkNo(string2long(value)); return true;
        default: return false;
    }
}

const char *P2P_ReqDescriptor::getFieldStructName(void *object, int field) const
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

void *P2P_ReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Req *pp = (P2P_Req *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(P2P_Resp);

P2P_Resp::P2P_Resp(const char *name, int kind) : P2P_Packet(name,kind)
{
    this->id_var = 0;
    this->chunkNo_var = 0;
    contents_arraysize = 0;
    this->contents_var = 0;
}

P2P_Resp::P2P_Resp(const P2P_Resp& other) : P2P_Packet(other)
{
    contents_arraysize = 0;
    this->contents_var = 0;
    copy(other);
}

P2P_Resp::~P2P_Resp()
{
    delete [] contents_var;
}

P2P_Resp& P2P_Resp::operator=(const P2P_Resp& other)
{
    if (this==&other) return *this;
    P2P_Packet::operator=(other);
    copy(other);
    return *this;
}

void P2P_Resp::copy(const P2P_Resp& other)
{
    this->id_var = other.id_var;
    this->chunkNo_var = other.chunkNo_var;
    delete [] this->contents_var;
    this->contents_var = (other.contents_arraysize==0) ? NULL : new char[other.contents_arraysize];
    contents_arraysize = other.contents_arraysize;
    for (unsigned int i=0; i<contents_arraysize; i++)
        this->contents_var[i] = other.contents_var[i];
}

void P2P_Resp::parsimPack(cCommBuffer *b)
{
    P2P_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    doPacking(b,this->chunkNo_var);
    b->pack(contents_arraysize);
    doPacking(b,this->contents_var,contents_arraysize);
}

void P2P_Resp::parsimUnpack(cCommBuffer *b)
{
    P2P_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->chunkNo_var);
    delete [] this->contents_var;
    b->unpack(contents_arraysize);
    if (contents_arraysize==0) {
        this->contents_var = 0;
    } else {
        this->contents_var = new char[contents_arraysize];
        doUnpacking(b,this->contents_var,contents_arraysize);
    }
}

const char * P2P_Resp::getId() const
{
    return id_var.c_str();
}

void P2P_Resp::setId(const char * id)
{
    this->id_var = id;
}

int P2P_Resp::getChunkNo() const
{
    return chunkNo_var;
}

void P2P_Resp::setChunkNo(int chunkNo)
{
    this->chunkNo_var = chunkNo;
}

void P2P_Resp::setContentsArraySize(unsigned int size)
{
    char *contents_var2 = (size==0) ? NULL : new char[size];
    unsigned int sz = contents_arraysize < size ? contents_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        contents_var2[i] = this->contents_var[i];
    for (unsigned int i=sz; i<size; i++)
        contents_var2[i] = 0;
    contents_arraysize = size;
    delete [] this->contents_var;
    this->contents_var = contents_var2;
}

unsigned int P2P_Resp::getContentsArraySize() const
{
    return contents_arraysize;
}

char P2P_Resp::getContents(unsigned int k) const
{
    if (k>=contents_arraysize) throw cRuntimeError("Array of size %d indexed by %d", contents_arraysize, k);
    return contents_var[k];
}

void P2P_Resp::setContents(unsigned int k, char contents)
{
    if (k>=contents_arraysize) throw cRuntimeError("Array of size %d indexed by %d", contents_arraysize, k);
    this->contents_var[k] = contents;
}

class P2P_RespDescriptor : public cClassDescriptor
{
  public:
    P2P_RespDescriptor();
    virtual ~P2P_RespDescriptor();

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

Register_ClassDescriptor(P2P_RespDescriptor);

P2P_RespDescriptor::P2P_RespDescriptor() : cClassDescriptor("P2P_Resp", "P2P_Packet")
{
}

P2P_RespDescriptor::~P2P_RespDescriptor()
{
}

bool P2P_RespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2P_Resp *>(obj)!=NULL;
}

const char *P2P_RespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2P_RespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int P2P_RespDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *P2P_RespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "chunkNo",
        "contents",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int P2P_RespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunkNo")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "contents")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2P_RespDescriptor::getFieldTypeString(void *object, int field) const
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
        "char",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *P2P_RespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int P2P_RespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Resp *pp = (P2P_Resp *)object; (void)pp;
    switch (field) {
        case 2: return pp->getContentsArraySize();
        default: return 0;
    }
}

std::string P2P_RespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Resp *pp = (P2P_Resp *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return long2string(pp->getChunkNo());
        case 2: return long2string(pp->getContents(i));
        default: return "";
    }
}

bool P2P_RespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Resp *pp = (P2P_Resp *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setChunkNo(string2long(value)); return true;
        case 2: pp->setContents(i,string2long(value)); return true;
        default: return false;
    }
}

const char *P2P_RespDescriptor::getFieldStructName(void *object, int field) const
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
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *P2P_RespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2P_Resp *pp = (P2P_Resp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


