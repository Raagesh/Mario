#include <game/model/network/Node.h>

namespace Ting
{

class NodeTest
{
public:
	void TestConnectNode()
	{
	}
	
	void TestSendMessage()
	{
	}
	
	void TestAddMessageReceivedListener()
	{
	}
	
	void TestRemoveMessageReceivedListener()
	{
	}
};

class SimulatedNetworkConditionsTest
{
public:
	void TestDeadConnection()
	{
	}

	void TestLatency()
	{
	}
	
	void TestDroppedPackets()
	{
	}
	
	void TestReorderedPackets()
	{
	}

	void TestFoo()
	{
		Network::Node node1("Node-1");
		Network::Node node2("Node-2");

		node1.ConnectNode(node2.GetId());

		//class MessageRecievedListener : public IMessageRecievedListener
		//{
		//public:
		//	void MessageRecieved(Network::Id from, std::string message)
		//	{
		//	}
		//} messageRecievedListener;

//		node1.AddMessageReceivedListener(messageRecievedListener);
//		node2.AddMessageReceivedListener(messageRecievedListener);
//
//		node1.SendMessage(node2, "node1 -> node2");
//#error Verify that the message was received.
//#error Measure the time the message took to arrive.
//		node2.SendMessage(node1, "node2 -> node1");
//#error Verify that the message was received.
//#error Measure the time the message took to arrive.
//
//		connection.SimulateLatency(Time::Milliseconds(500));
//		
//		node1.SendMessage(node2, "node1 -> node2");
//#error Verify that the message was received.
//#error Measure the time the message took to arrive.
//		node2.SendMessage(node1, "node2 -> node1");
//#error Verify that the message was received.
//#error Measure the time the message took to arrive.
	}
};

} // namespace Ting