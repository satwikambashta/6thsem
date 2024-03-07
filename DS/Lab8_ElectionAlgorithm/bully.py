'''
Simulate a scenario in distributed systems to implement the Bully Algorithm for choosing
a coordinator node amongst the participative nodes of the system after the collapse of the
existing coordinator node in the system.
'''
nodes = [Node(1), Node(2), Node(4), Node(5), Node(6), Node(8)]
class Node:
    def __init__(self, id):
        self.id = id
        self.is_coordinator = False

    def send_election_message(self, other_nodes):
	    print(f"Node {self.id} is initiating an election.")
	    responses = self.get_responses(other_nodes)
	    if not responses: # Check if responses list is empty
	        print(f"Node {self.id} wins the election due to no responses.")
	        self.is_coordinator = True
	    elif self.id == max(responses):
	        self.is_coordinator = True
	        print(f"Node {self.id} has been elected as the coordinator.")
	    else:
	        starting(self.id+1)


    def get_responses(self, other_nodes):
        responses = []
        for node in other_nodes:
            if node.id > self.id:
                responses.append(node.id)
        return responses



def starting(iden):
	# Node 5 initiates the election
	for node in nodes:
	    if node.id == iden:
	        node.send_election_message(nodes)


def main():
	
	starting(5)

if __name__ =="__main__":
	main()