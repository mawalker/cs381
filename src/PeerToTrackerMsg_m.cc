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
    e->insert(P2T_REG_REQUEST, "P2T_REG_REQUEST");
    e->insert(P2T_REFRESH_REQUEST, "P2T_REFRESH_REQUEST");
    e->insert(T2P_MEMBER_RESPONSE, "T2P_MEMBER_RESPONSE");
    e->insert(P2T_DOWNLOAD_COMPLETE, "P2T_DOWNLOAD_COMPLETE");
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

Register_Class(CHUNKS_OWNED_Msg);

CHUNKS_OWNED_Msg::CHUNKS_OWNED_Msg(const char *name, int kind) : P2T_Packet(name,kind)
{
    this->id_var = 0;
    downloadedChunks_arraysize = 0;
    this->downloadedChunks_var = 0;
}

CHUNKS_OWNED_Msg::CHUNKS_OWNED_Msg(const CHUNKS_OWNED_Msg& other) : P2T_Packet(other)
{
    downloadedChunks_arraysize = 0;
    this->downloadedChunks_var = 0;
    copy(other);
}

CHUNKS_OWNED_Msg::~CHUNKS_OWNED_Msg()
{
    delete [] downloadedChunks_var;
}

CHUNKS_OWNED_Msg& CHUNKS_OWNED_Msg::operator=(const CHUNKS_OWNED_Msg& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void CHUNKS_OWNED_Msg::copy(const CHUNKS_OWNED_Msg& other)
{
    this->id_var = other.id_var;
    delete [] this->downloadedChunks_var;
    this->downloadedChunks_var = (other.downloadedChunks_arraysize==0) ? NULL : new int[other.downloadedChunks_arraysize];
    downloadedChunks_arraysize = other.downloadedChunks_arraysize;
    for (unsigned int i=0; i<downloadedChunks_arraysize; i++)
        this->downloadedChunks_var[i] = other.downloadedChunks_var[i];
}

void CHUNKS_OWNED_Msg::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    doPacking(b,this->id_var);
    b->pack(downloadedChunks_arraysize);
    doPacking(b,this->downloadedChunks_var,downloadedChunks_arraysize);
}

void CHUNKS_OWNED_Msg::parsimUnpack(cCommBuffer *b)
{
    P2T_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
    delete [] this->downloadedChunks_var;
    b->unpack(downloadedChunks_arraysize);
    if (downloadedChunks_arraysize==0) {
        this->downloadedChunks_var = 0;
    } else {
        this->downloadedChunks_var = new int[downloadedChunks_arraysize];
        doUnpacking(b,this->downloadedChunks_var,downloadedChunks_arraysize);
    }
}

const char * CHUNKS_OWNED_Msg::getId() const
{
    return id_var.c_str();
}

void CHUNKS_OWNED_Msg::setId(const char * id)
{
    this->id_var = id;
}

void CHUNKS_OWNED_Msg::setDownloadedChunksArraySize(unsigned int size)
{
    int *downloadedChunks_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = downloadedChunks_arraysize < size ? downloadedChunks_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        downloadedChunks_var2[i] = this->downloadedChunks_var[i];
    for (unsigned int i=sz; i<size; i++)
        downloadedChunks_var2[i] = 0;
    downloadedChunks_arraysize = size;
    delete [] this->downloadedChunks_var;
    this->downloadedChunks_var = downloadedChunks_var2;
}

unsigned int CHUNKS_OWNED_Msg::getDownloadedChunksArraySize() const
{
    return downloadedChunks_arraysize;
}

int CHUNKS_OWNED_Msg::getDownloadedChunks(unsigned int k) const
{
    if (k>=downloadedChunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", downloadedChunks_arraysize, k);
    return downloadedChunks_var[k];
}

void CHUNKS_OWNED_Msg::setDownloadedChunks(unsigned int k, int downloadedChunks)
{
    if (k>=downloadedChunks_arraysize) throw cRuntimeError("Array of size %d indexed by %d", downloadedChunks_arraysize, k);
    this->downloadedChunks_var[k] = downloadedChunks;
}

class CHUNKS_OWNED_MsgDescriptor : public cClassDescriptor
{
  public:
    CHUNKS_OWNED_MsgDescriptor();
    virtual ~CHUNKS_OWNED_MsgDescriptor();

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

Register_ClassDescriptor(CHUNKS_OWNED_MsgDescriptor);

CHUNKS_OWNED_MsgDescriptor::CHUNKS_OWNED_MsgDescriptor() : cClassDescriptor("CHUNKS_OWNED_Msg", "P2T_Packet")
{
}

CHUNKS_OWNED_MsgDescriptor::~CHUNKS_OWNED_MsgDescriptor()
{
}

bool CHUNKS_OWNED_MsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CHUNKS_OWNED_Msg *>(obj)!=NULL;
}

const char *CHUNKS_OWNED_MsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CHUNKS_OWNED_MsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int CHUNKS_OWNED_MsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *CHUNKS_OWNED_MsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "id",
        "downloadedChunks",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int CHUNKS_OWNED_MsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "downloadedChunks")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CHUNKS_OWNED_MsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *CHUNKS_OWNED_MsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int CHUNKS_OWNED_MsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CHUNKS_OWNED_Msg *pp = (CHUNKS_OWNED_Msg *)object; (void)pp;
    switch (field) {
        case 1: return pp->getDownloadedChunksArraySize();
        default: return 0;
    }
}

std::string CHUNKS_OWNED_MsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CHUNKS_OWNED_Msg *pp = (CHUNKS_OWNED_Msg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        case 1: return long2string(pp->getDownloadedChunks(i));
        default: return "";
    }
}

bool CHUNKS_OWNED_MsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CHUNKS_OWNED_Msg *pp = (CHUNKS_OWNED_Msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        case 1: pp->setDownloadedChunks(i,string2long(value)); return true;
        default: return false;
    }
}

const char *CHUNKS_OWNED_MsgDescriptor::getFieldStructName(void *object, int field) const
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

void *CHUNKS_OWNED_MsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CHUNKS_OWNED_Msg *pp = (CHUNKS_OWNED_Msg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(T2P_MEMBER_Res);

T2P_MEMBER_Res::T2P_MEMBER_Res(const char *name, int kind) : P2T_Packet(name,kind)
{
    ids_arraysize = 0;
    this->ids_var = 0;
    chunksOwned_arraysize = 0;
    this->chunksOwned_var = 0;
}

T2P_MEMBER_Res::T2P_MEMBER_Res(const T2P_MEMBER_Res& other) : P2T_Packet(other)
{
    ids_arraysize = 0;
    this->ids_var = 0;
    chunksOwned_arraysize = 0;
    this->chunksOwned_var = 0;
    copy(other);
}

T2P_MEMBER_Res::~T2P_MEMBER_Res()
{
    delete [] ids_var;
    for (unsigned int i=0; i<chunksOwned_arraysize; i++)
        drop(&(this->chunksOwned_var[i]));
    delete [] chunksOwned_var;
}

T2P_MEMBER_Res& T2P_MEMBER_Res::operator=(const T2P_MEMBER_Res& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void T2P_MEMBER_Res::copy(const T2P_MEMBER_Res& other)
{
    delete [] this->ids_var;
    this->ids_var = (other.ids_arraysize==0) ? NULL : new opp_string[other.ids_arraysize];
    ids_arraysize = other.ids_arraysize;
    for (unsigned int i=0; i<ids_arraysize; i++)
        this->ids_var[i] = other.ids_var[i];
    delete [] this->chunksOwned_var;
    this->chunksOwned_var = (other.chunksOwned_arraysize==0) ? NULL : new CHUNKS_OWNED_Msg[other.chunksOwned_arraysize];
    chunksOwned_arraysize = other.chunksOwned_arraysize;
    for (unsigned int i=0; i<chunksOwned_arraysize; i++)
    {
        take(&(this->chunksOwned_var[i]));
        this->chunksOwned_var[i] = other.chunksOwned_var[i];
        this->chunksOwned_var[i].setName(other.chunksOwned_var[i].getName());
    }
}

void T2P_MEMBER_Res::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    b->pack(ids_arraysize);
    doPacking(b,this->ids_var,ids_arraysize);
    b->pack(chunksOwned_arraysize);
    doPacking(b,this->chunksOwned_var,chunksOwned_arraysize);
}

void T2P_MEMBER_Res::parsimUnpack(cCommBuffer *b)
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
    delete [] this->chunksOwned_var;
    b->unpack(chunksOwned_arraysize);
    if (chunksOwned_arraysize==0) {
        this->chunksOwned_var = 0;
    } else {
        this->chunksOwned_var = new CHUNKS_OWNED_Msg[chunksOwned_arraysize];
        doUnpacking(b,this->chunksOwned_var,chunksOwned_arraysize);
    }
}

void T2P_MEMBER_Res::setIdsArraySize(unsigned int size)
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

unsigned int T2P_MEMBER_Res::getIdsArraySize() const
{
    return ids_arraysize;
}

const char * T2P_MEMBER_Res::getIds(unsigned int k) const
{
    if (k>=ids_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ids_arraysize, k);
    return ids_var[k].c_str();
}

void T2P_MEMBER_Res::setIds(unsigned int k, const char * ids)
{
    if (k>=ids_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ids_arraysize, k);
    this->ids_var[k] = ids;
}

void T2P_MEMBER_Res::setChunksOwnedArraySize(unsigned int size)
{
    CHUNKS_OWNED_Msg *chunksOwned_var2 = (size==0) ? NULL : new CHUNKS_OWNED_Msg[size];
    unsigned int sz = chunksOwned_arraysize < size ? chunksOwned_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        chunksOwned_var2[i] = this->chunksOwned_var[i];
    for (unsigned int i=sz; i<size; i++)
        take(&(chunksOwned_var2[i]));
    chunksOwned_arraysize = size;
    delete [] this->chunksOwned_var;
    this->chunksOwned_var = chunksOwned_var2;
}

unsigned int T2P_MEMBER_Res::getChunksOwnedArraySize() const
{
    return chunksOwned_arraysize;
}

CHUNKS_OWNED_Msg& T2P_MEMBER_Res::getChunksOwned(unsigned int k)
{
    if (k>=chunksOwned_arraysize) throw cRuntimeError("Array of size %d indexed by %d", chunksOwned_arraysize, k);
    return chunksOwned_var[k];
}

void T2P_MEMBER_Res::setChunksOwned(unsigned int k, const CHUNKS_OWNED_Msg& chunksOwned)
{
    if (k>=chunksOwned_arraysize) throw cRuntimeError("Array of size %d indexed by %d", chunksOwned_arraysize, k);
    this->chunksOwned_var[k] = chunksOwned;
}

class T2P_MEMBER_ResDescriptor : public cClassDescriptor
{
  public:
    T2P_MEMBER_ResDescriptor();
    virtual ~T2P_MEMBER_ResDescriptor();

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

Register_ClassDescriptor(T2P_MEMBER_ResDescriptor);

T2P_MEMBER_ResDescriptor::T2P_MEMBER_ResDescriptor() : cClassDescriptor("T2P_MEMBER_Res", "P2T_Packet")
{
}

T2P_MEMBER_ResDescriptor::~T2P_MEMBER_ResDescriptor()
{
}

bool T2P_MEMBER_ResDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<T2P_MEMBER_Res *>(obj)!=NULL;
}

const char *T2P_MEMBER_ResDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int T2P_MEMBER_ResDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int T2P_MEMBER_ResDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *T2P_MEMBER_ResDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ids",
        "chunksOwned",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int T2P_MEMBER_ResDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "ids")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunksOwned")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *T2P_MEMBER_ResDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "CHUNKS_OWNED_Msg",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *T2P_MEMBER_ResDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int T2P_MEMBER_ResDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBER_Res *pp = (T2P_MEMBER_Res *)object; (void)pp;
    switch (field) {
        case 0: return pp->getIdsArraySize();
        case 1: return pp->getChunksOwnedArraySize();
        default: return 0;
    }
}

std::string T2P_MEMBER_ResDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBER_Res *pp = (T2P_MEMBER_Res *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getIds(i));
        case 1: {std::stringstream out; out << pp->getChunksOwned(i); return out.str();}
        default: return "";
    }
}

bool T2P_MEMBER_ResDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBER_Res *pp = (T2P_MEMBER_Res *)object; (void)pp;
    switch (field) {
        case 0: pp->setIds(i,(value)); return true;
        default: return false;
    }
}

const char *T2P_MEMBER_ResDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "CHUNKS_OWNED_Msg",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *T2P_MEMBER_ResDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    T2P_MEMBER_Res *pp = (T2P_MEMBER_Res *)object; (void)pp;
    switch (field) {
        case 1: return (void *)static_cast<cObject *>(&pp->getChunksOwned(i)); break;
        default: return NULL;
    }
}

Register_Class(P2T_DOWNLOAD_COMPLETE_Msg);

P2T_DOWNLOAD_COMPLETE_Msg::P2T_DOWNLOAD_COMPLETE_Msg(const char *name, int kind) : P2T_Packet(name,kind)
{
    this->id_var = 0;
}

P2T_DOWNLOAD_COMPLETE_Msg::P2T_DOWNLOAD_COMPLETE_Msg(const P2T_DOWNLOAD_COMPLETE_Msg& other) : P2T_Packet(other)
{
    copy(other);
}

P2T_DOWNLOAD_COMPLETE_Msg::~P2T_DOWNLOAD_COMPLETE_Msg()
{
}

P2T_DOWNLOAD_COMPLETE_Msg& P2T_DOWNLOAD_COMPLETE_Msg::operator=(const P2T_DOWNLOAD_COMPLETE_Msg& other)
{
    if (this==&other) return *this;
    P2T_Packet::operator=(other);
    copy(other);
    return *this;
}

void P2T_DOWNLOAD_COMPLETE_Msg::copy(const P2T_DOWNLOAD_COMPLETE_Msg& other)
{
    this->id_var = other.id_var;
}

void P2T_DOWNLOAD_COMPLETE_Msg::parsimPack(cCommBuffer *b)
{
    P2T_Packet::parsimPack(b);
    doPacking(b,this->id_var);
}

void P2T_DOWNLOAD_COMPLETE_Msg::parsimUnpack(cCommBuffer *b)
{
    P2T_Packet::parsimUnpack(b);
    doUnpacking(b,this->id_var);
}

const char * P2T_DOWNLOAD_COMPLETE_Msg::getId() const
{
    return id_var.c_str();
}

void P2T_DOWNLOAD_COMPLETE_Msg::setId(const char * id)
{
    this->id_var = id;
}

class P2T_DOWNLOAD_COMPLETE_MsgDescriptor : public cClassDescriptor
{
  public:
    P2T_DOWNLOAD_COMPLETE_MsgDescriptor();
    virtual ~P2T_DOWNLOAD_COMPLETE_MsgDescriptor();

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

Register_ClassDescriptor(P2T_DOWNLOAD_COMPLETE_MsgDescriptor);

P2T_DOWNLOAD_COMPLETE_MsgDescriptor::P2T_DOWNLOAD_COMPLETE_MsgDescriptor() : cClassDescriptor("P2T_DOWNLOAD_COMPLETE_Msg", "P2T_Packet")
{
}

P2T_DOWNLOAD_COMPLETE_MsgDescriptor::~P2T_DOWNLOAD_COMPLETE_MsgDescriptor()
{
}

bool P2T_DOWNLOAD_COMPLETE_MsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2T_DOWNLOAD_COMPLETE_Msg *>(obj)!=NULL;
}

const char *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldName(void *object, int field) const
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

int P2T_DOWNLOAD_COMPLETE_MsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2T_DOWNLOAD_COMPLETE_Msg *pp = (P2T_DOWNLOAD_COMPLETE_Msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_DOWNLOAD_COMPLETE_Msg *pp = (P2T_DOWNLOAD_COMPLETE_Msg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getId());
        default: return "";
    }
}

bool P2T_DOWNLOAD_COMPLETE_MsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2T_DOWNLOAD_COMPLETE_Msg *pp = (P2T_DOWNLOAD_COMPLETE_Msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setId((value)); return true;
        default: return false;
    }
}

const char *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldStructName(void *object, int field) const
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

void *P2T_DOWNLOAD_COMPLETE_MsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2T_DOWNLOAD_COMPLETE_Msg *pp = (P2T_DOWNLOAD_COMPLETE_Msg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


