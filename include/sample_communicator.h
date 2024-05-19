#ifndef __SAMPLE_CLASS_H__
#define __SAMPLE_CLASS_H__

#include <iostream>
#include <cstdint>
#include <string>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Connector{
public:
  Connector(){};
  virtual ~Connector(){};
  virtual uint32_t SendDevice(
    uint32_t  mode,
    void      *data
  ) = 0;
  virtual uint32_t ReceiveData(
    void      *data,
    uint32_t  size
  ) = 0;
};


class MockConnector : public Connector{
public:
  uint32_t ReceiveData(void *data, uint32_t size) override{
    uint32_t  ret = 0;
    std::unique_ptr<uint8_t[]>  tmp_data = std::make_unique<uint8_t[]>(size);

    ret = ReceiveDataMock(tmp_data.get(), size);
    std::copy(tmp_data.get(), (tmp_data.get()+size), reinterpret_cast<uint8_t*>(data));
    return ret;
  };

  MOCK_METHOD(
    uint32_t,
    SendDevice,
    (
      uint32_t,
      void *
    )
  );
  MOCK_METHOD(
    uint32_t,
    ReceiveDataMock,
    (
      uint8_t *,
      uint32_t
    )
  );
};


class Communicator {
private:
  Connector *connector_;

public:
  Communicator(Connector *connector)
  : connector_(connector)
  {};
  virtual ~Communicator(){};

  uint32_t Send(
    void      *data,
    uint32_t  mode
  );
  uint32_t Receive(
    void      *data,
    uint32_t  size
  );

};

#endif