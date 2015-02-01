/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "stu_types.h"

#include <algorithm>



const char* StudentRequest::ascii_fingerprint = "457B6E35E5EAAA1DBF18D6B3763BD82E";
const uint8_t StudentRequest::binary_fingerprint[16] = {0x45,0x7B,0x6E,0x35,0xE5,0xEA,0xAA,0x1D,0xBF,0x18,0xD6,0xB3,0x76,0x3B,0xD8,0x2E};

uint32_t StudentRequest::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->sno);
          this->__isset.sno = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->sname);
          this->__isset.sname = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->ssex);
          this->__isset.ssex = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->sage);
          this->__isset.sage = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t StudentRequest::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("StudentRequest");

  xfer += oprot->writeFieldBegin("sno", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->sno);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sname", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->sname);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("ssex", ::apache::thrift::protocol::T_BOOL, 3);
  xfer += oprot->writeBool(this->ssex);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sage", ::apache::thrift::protocol::T_I16, 4);
  xfer += oprot->writeI16(this->sage);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(StudentRequest &a, StudentRequest &b) {
  using ::std::swap;
  swap(a.sno, b.sno);
  swap(a.sname, b.sname);
  swap(a.ssex, b.ssex);
  swap(a.sage, b.sage);
  swap(a.__isset, b.__isset);
}

const char* StudentResult::ascii_fingerprint = "3F5FC93B338687BC7235B1AB103F47B3";
const uint8_t StudentResult::binary_fingerprint[16] = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

uint32_t StudentResult::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->ret);
          this->__isset.ret = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->smsg);
          this->__isset.smsg = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t StudentResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("StudentResult");

  xfer += oprot->writeFieldBegin("ret", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->ret);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("smsg", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->smsg);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(StudentResult &a, StudentResult &b) {
  using ::std::swap;
  swap(a.ret, b.ret);
  swap(a.smsg, b.smsg);
  swap(a.__isset, b.__isset);
}


