//
// Generated file, do not edit! Created by opp_msgc 4.3 from ClientServerAppMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ClientServerAppMsg_m.h"

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
    cEnum *e = cEnum::find("CS_MSG_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("CS_MSG_TYPE"));
    e->insert(CS_REQUEST, "CS_REQUEST");
    e->insert(CS_RESPONSE, "CS_RESPONSE");
);

Register_Class(CS_Packet);

CS_Packet::CS_Packet(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
}

CS_Packet::CS_Packet(const CS_Packet& other) : cPacket(other)
{
    copy(other);
}

CS_Packet::~CS_Packet()
{
}

CS_Packet& CS_Packet::operator=(const CS_Packet& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void CS_Packet::copy(const CS_Packet& other)
{
    this->type_var = other.type_var;
}

void CS_Packet::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void CS_Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int CS_Packet::getType() const
{
    return type_var;
}

void CS_Packet::setType(int type)
{
    this->type_var = type;
}

class CS_PacketDescriptor : public cClassDescriptor
{
  public:
    CS_PacketDescriptor();
    virtual ~CS_PacketDescriptor();

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

Register_ClassDescriptor(CS_PacketDescriptor);

CS_PacketDescriptor::CS_PacketDescriptor() : cClassDescriptor("CS_Packet", "cPacket")
{
}

CS_PacketDescriptor::~CS_PacketDescriptor()
{
}

bool CS_PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CS_Packet *>(obj)!=NULL;
}

const char *CS_PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CS_PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CS_PacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *CS_PacketDescriptor::getFieldName(void *object, int field) const
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

int CS_PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CS_PacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *CS_PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "CS_MSG_TYPE";
            return NULL;
        default: return NULL;
    }
}

int CS_PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CS_Packet *pp = (CS_Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CS_PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Packet *pp = (CS_Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool CS_PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CS_Packet *pp = (CS_Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *CS_PacketDescriptor::getFieldStructName(void *object, int field) const
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

void *CS_PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Packet *pp = (CS_Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CS_Req);

CS_Req::CS_Req(const char *name, int kind) : CS_Packet(name,kind)
{
    this->id_var = 0;
    this->filesize_var = 0;
    this->fname_var = 0;
}

CS_Req::CS_Req(const CS_Req& other) : CS_Packet(other)
{
    copy(other);
}

CS_Req::~CS_Req()
{
}

CS_Req& CS_Req::operator=(const CS_Req& other)
{
    if (this==&other) return *this;
    CS_Packet::operator=(other);
    copy(other);
    return *this;
}

void CS_Req::copy(const CS_Req& other)
{
    this->id_var = other.id_var;
    this->filesize_var = other.filesize_var;
    this->fname_var = other.fname_var;
}

void CS_Req::parsimPack(cCommBuffer *b)
{
    CS_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    doPacking(b,this->filesize_var);
    doPacking(b,this->fname_var);
}

void CS_Req::parsimUnpack(cCommBuffer *b)
{
    CS_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->filesize_var);
    doUnpacking(b,this->fname_var);
}

const char * CS_Req::getId() const
{
    return id_var.c_str();
}

void CS_Req::setId(const char * id)
{
    this->id_var = id;
}

int CS_Req::getFilesize() const
{
    return filesize_var;
}

void CS_Req::setFilesize(int filesize)
{
    this->filesize_var = filesize;
}

const char * CS_Req::getFname() const
{
    return fname_var.c_str();
}

void CS_Req::setFname(const char * fname)
{
    this->fname_var = fname;
}

class CS_ReqDescriptor : public cClassDescriptor
{
  public:
    CS_ReqDescriptor();
    virtual ~CS_ReqDescriptor();

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

Register_ClassDescriptor(CS_ReqDescriptor);

CS_ReqDescriptor::CS_ReqDescriptor() : cClassDescriptor("CS_Req", "CS_Packet")
{
}

CS_ReqDescriptor::~CS_ReqDescriptor()
{
}

bool CS_ReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CS_Req *>(obj)!=NULL;
}

const char *CS_ReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CS_ReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int CS_ReqDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *CS_ReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "filesize",
        "fname",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int CS_ReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "filesize")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "fname")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CS_ReqDescriptor::getFieldTypeString(void *object, int field) const
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
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *CS_ReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int CS_ReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CS_Req *pp = (CS_Req *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CS_ReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Req *pp = (CS_Req *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return long2string(pp->getFilesize());
        case 2: return oppstring2string(pp->getFname());
        default: return "";
    }
}

bool CS_ReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CS_Req *pp = (CS_Req *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setFilesize(string2long(value)); return true;
        case 2: pp->setFname((value)); return true;
        default: return false;
    }
}

const char *CS_ReqDescriptor::getFieldStructName(void *object, int field) const
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

void *CS_ReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Req *pp = (CS_Req *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CS_Resp);

CS_Resp::CS_Resp(const char *name, int kind) : CS_Packet(name,kind)
{
    this->id_var = 0;
    this->size_var = 0;
    data_arraysize = 0;
    this->data_var = 0;
}

CS_Resp::CS_Resp(const CS_Resp& other) : CS_Packet(other)
{
    data_arraysize = 0;
    this->data_var = 0;
    copy(other);
}

CS_Resp::~CS_Resp()
{
    delete [] data_var;
}

CS_Resp& CS_Resp::operator=(const CS_Resp& other)
{
    if (this==&other) return *this;
    CS_Packet::operator=(other);
    copy(other);
    return *this;
}

void CS_Resp::copy(const CS_Resp& other)
{
    this->id_var = other.id_var;
    this->size_var = other.size_var;
    delete [] this->data_var;
    this->data_var = (other.data_arraysize==0) ? NULL : new char[other.data_arraysize];
    data_arraysize = other.data_arraysize;
    for (unsigned int i=0; i<data_arraysize; i++)
        this->data_var[i] = other.data_var[i];
}

void CS_Resp::parsimPack(cCommBuffer *b)
{
    CS_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    doPacking(b,this->size_var);
    b->pack(data_arraysize);
    doPacking(b,this->data_var,data_arraysize);
}

void CS_Resp::parsimUnpack(cCommBuffer *b)
{
    CS_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->size_var);
    delete [] this->data_var;
    b->unpack(data_arraysize);
    if (data_arraysize==0) {
        this->data_var = 0;
    } else {
        this->data_var = new char[data_arraysize];
        doUnpacking(b,this->data_var,data_arraysize);
    }
}

const char * CS_Resp::getId() const
{
    return id_var.c_str();
}

void CS_Resp::setId(const char * id)
{
    this->id_var = id;
}

unsigned long CS_Resp::getSize() const
{
    return size_var;
}

void CS_Resp::setSize(unsigned long size)
{
    this->size_var = size;
}

void CS_Resp::setDataArraySize(unsigned int size)
{
    char *data_var2 = (size==0) ? NULL : new char[size];
    unsigned int sz = data_arraysize < size ? data_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        data_var2[i] = this->data_var[i];
    for (unsigned int i=sz; i<size; i++)
        data_var2[i] = 0;
    data_arraysize = size;
    delete [] this->data_var;
    this->data_var = data_var2;
}

unsigned int CS_Resp::getDataArraySize() const
{
    return data_arraysize;
}

char CS_Resp::getData(unsigned int k) const
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    return data_var[k];
}

void CS_Resp::setData(unsigned int k, char data)
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    this->data_var[k] = data;
}

class CS_RespDescriptor : public cClassDescriptor
{
  public:
    CS_RespDescriptor();
    virtual ~CS_RespDescriptor();

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

Register_ClassDescriptor(CS_RespDescriptor);

CS_RespDescriptor::CS_RespDescriptor() : cClassDescriptor("CS_Resp", "CS_Packet")
{
}

CS_RespDescriptor::~CS_RespDescriptor()
{
}

bool CS_RespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CS_Resp *>(obj)!=NULL;
}

const char *CS_RespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CS_RespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int CS_RespDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *CS_RespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "size",
        "data",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int CS_RespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CS_RespDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "unsigned long",
        "char",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *CS_RespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int CS_RespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CS_Resp *pp = (CS_Resp *)object; (void)pp;
    switch (field) {
        case 2: return pp->getDataArraySize();
        default: return 0;
    }
}

std::string CS_RespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Resp *pp = (CS_Resp *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return ulong2string(pp->getSize());
        case 2: return long2string(pp->getData(i));
        default: return "";
    }
}

bool CS_RespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CS_Resp *pp = (CS_Resp *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setSize(string2ulong(value)); return true;
        case 2: pp->setData(i,string2long(value)); return true;
        default: return false;
    }
}

const char *CS_RespDescriptor::getFieldStructName(void *object, int field) const
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

void *CS_RespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CS_Resp *pp = (CS_Resp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


