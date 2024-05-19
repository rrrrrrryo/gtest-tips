#include <iostream>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "sample_communicator.h"

int32_t TimesCalc(int32_t a, int32_t b){
  return a * b;
}

TEST(TestTips, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(TimesCalc(7,6), 42);
}

TEST(TestTips, BasicMock){
  uint32_t ret  = 0;
  uint32_t mode = 1;
  MockConnector mock_connector;
  Communicator  communicator(&mock_connector);

  EXPECT_CALL(mock_connector, SendDevice(mode, testing::_))
  .Times(1)
  .WillOnce(testing::Return(0));

  ret = communicator.Send(nullptr, mode);

  EXPECT_EQ(ret, 0);
}

TEST(TestTips, ReturnPointerMock1){
  uint32_t ret = 0;
  MockConnector mock_connector;
  Communicator  communicator(&mock_connector);

  uint32_t expect_data = 10;
  std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(sizeof(uint32_t));

  EXPECT_CALL(mock_connector, ReceiveDataMock(testing::_, sizeof(uint32_t)))
  .Times(1)
  .WillOnce(
    testing::DoAll(
      testing::SetArgPointee<0>(expect_data),
      testing::Return(0)
    )
  );

  ret = communicator.Receive(reinterpret_cast<void*>(data.get()), sizeof(uint32_t));

  EXPECT_EQ(ret, 0);
  EXPECT_EQ(*reinterpret_cast<uint32_t*>(data.get()), expect_data);
}

TEST(TestTips, ReturnPointerMock2){
  uint32_t ret = 0;
  MockConnector mock_connector;
  Communicator communicator(&mock_connector);

  std::string expect_data = "hello world";
  std::string data;

  uint32_t size = expect_data.size();

  EXPECT_CALL(mock_connector, ReceiveDataMock(testing::_, size))
  .Times(1)
  .WillOnce(
    testing::DoAll(
      testing::SetArrayArgument<0>(expect_data.c_str(), expect_data.c_str()+size),
      testing::Return(0)
    )
  );

  ret = communicator.Receive(reinterpret_cast<void*>(const_cast<char*>(data.c_str())), size);

  EXPECT_EQ(ret, 0);
  EXPECT_STREQ(data.c_str(), expect_data.c_str());
}
