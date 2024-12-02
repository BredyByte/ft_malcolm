# ft_malcolm

> This repository contains a "ft_malcolm" project that is part of the École 42 curriculum.

## Overview
ft_malcolm is a 42 École outer core project focused on networking and cybersecurity. The goal is to develop a program in C that performs MAC address spoofing, allowing manipulation of a victim's network traffic by impersonating critical network devices, such as the gateway, within the **Local Area Network (LAN)**.

This project provides hands-on experience with Layer 2 (Data Link Layer) of the **OSI** model and introduces key networking concepts such as: *Host, Node, Packet, Protocol, IP, MAC, LAN, and ARP*. By working on ft_malcolm, students gain practical knowledge of network packet manipulation, enabling them to understand the inner workings of network communication and security.

## RFC 826 and RFC 7042

To enhance understanding and provide a solid theoretical foundation for ft_malcolm, it's essential to explore relevant **RFCs (Request for Comments)**. RFCs are technical documents and standards published by the **Internet Engineering Task Force (IETF)** to define protocols and technologies foundational to the internet. For instance, RFC 1918 defines private IP address ranges, while RFC 2616 outlines the HTTP/1.1 protocol used for web communication.

### What is RFC 826?

**RFC 826**, titled *Address Resolution Protocol (ARP)*, defines the protocol used to map IP addresses to MAC addresses within a LAN. ARP is essential for communication between devices on the same network, as it allows the system to resolve an IP address into a physical MAC address. Without ARP, devices in a LAN wouldn’t be able to discover or communicate with each other efficiently.

### What is RFC 7042?

**RFC 7042**, titled *IANA Considerations and IETF Protocol and Documentation Usage for IEEE 802 Parameters*, focuses on the standardization and documentation of Ethernet parameters, including MAC address usage and Ethernet frame structures. This RFC ensures consistency and clarity in how MAC addresses and related network information are handled, which is crucial when implementing MAC spoofing techniques like those used in ft_malcolm.

### Understanding ARP (Address Resolution Protocol)

ARP is a fundamental protocol used in LANs to map IP addresses to MAC addresses. It operates at Layer 2 (Data Link Layer) of the OSI model and works as follows:

- **Request**: When a device needs to communicate with another device in the same network, it broadcasts an ARP request packet containing the target IP address.
- **Response**: The device with the matching IP responds with its MAC address, allowing the initiator to establish direct communication.

Below is the structure of an ARP packet, represented in C, including the Ethernet and ARP headers:
```c
// Ethernet header
typedef struct __attribute__((packed)) {
    uint8_t dest_mac[ETH_ALEN];     // Destination MAC address
    uint8_t src_mac[ETH_ALEN];      // Source MAC address
    uint16_t ethertype;             // Protocol type (e.g. 0x0806 for ARP)
} t_ethernet_header;

// ARP header
typedef struct __attribute__((packed)) {
    uint16_t htype;                 // Hardware Type (1 for Ethernet)
    uint16_t ptype;                 // Protocol Type (0x0800 for IPv4)
    uint8_t hlen;                   // MAC Address Length
    uint8_t plen;                   // IP Address Length
    uint16_t operation;             // Operation (1 for ARP Request, 2 for ARP Reply)
    uint8_t sender_mac[ETH_ALEN];   // Sender's MAC address
    uint8_t sender_ip[INET4_LEN];   // Sender's IP Address
    uint8_t target_mac[ETH_ALEN];   // Target's MAC address
    uint8_t target_ip[INET4_LEN];   // Target's IP address
} t_arp_header;
```

In ft_malcolm, ARP spoofing exploits this process by sending fake ARP responses, allowing the attacker to intercept, monitor, or manipulate the victim's network traffic by pretending to be a trusted network device, such as the gateway.

For more detailed information on key networking concepts, please refer to the attached file: **Theory.pdf**.

## How ft_malcolm Works

When I started working on ft_malcolm, I faced a lot of questions: how does the program work, how do you run it, what arguments should be used, how to test it, and what role do virtual machines play in this project? Below are detailed explanations to help understand how the project works and how to use it properly.

### Program Arguments

The program takes four arguments when executed:
1. **source_ip**: The IP address that the victim (target) is looking for. This is the target IP address that the victim sends ARP requests for.
1. **source_mac**: The MAC address the attacker will impersonate in the ARP reply. This is the fake MAC address sent to the victim, which will replace the real MAC address of the device with source_ip.
1. **target_ip**: The victim’s IP address. This is the IP address of the device that sends ARP requests. The program waits for ARP requests from this address and responds with a spoofed ARP reply.
1. **target_mac**: The victim’s MAC address. This is the MAC address of the device sending the ARP request and is used to send the spoofed ARP reply to the correct recipient.

### Program Execution Example

Imagine a network with two devices:
- **Device A (Victim)**: IP `10.0.0.20`, MAC `AA:BB:CC:DD:EE:FF`
- **Device B (Router)**: IP `10.0.0.1`, MAC `11:22:33:44:55:66`

You want to spoof the ARP entries on **Device A** to make it believe that the router’s IP (`10.0.0.1`) is associated with your machine’s MAC address (`FF:EE:DD:CC:BB:AA`).

Command execution:
```bash
sudo ./ft_malcolm 10.0.0.1 FF:EE:DD:CC:BB:AA 10.0.0.20 AA:BB:CC:DD:EE:FF
```

### Program Behavior

* **Wait for ARP Requests**: The program waits for Device A to send an ARP request to find the MAC address for `10.0.0.1`. ARP requests are broadcast (put as dest_mac `FF:FF:FF:FF:FF:FF`) messages visible to all devices on the network.
* **Reply with Spoofed Information**: When an ARP request is detected, the program sends a spoofed ARP reply to **Device A**, claiming that the IP address `10.0.0.1` (Router) is associated with your MAC address `FF:EE:DD:CC:BB:AA`.
* **Update ARP Table**: **Device A** updates its ARP table with this new information, associating `10.0.0.1` with your MAC address.
* **Program Exit**: After sending the spoofed ARP reply, the program exits. **Device A** will now route traffic intended for the router to your machine instead.

### Setting Up Virtual Machines
For the ft_malcolm project, you will need to set up two virtual machines: one for the attacker (**malcolm**) and one for the victim (**victim**). In my case, I used two **Debian 11.6.0** virtual machines with the following extensions installed: *vim net-tools iproute2 arping iputils-ping tcpdump*

Both virtual machines will use the **NAT Network** for networking. Here’s how to set it up in **Oracle VM VirtualBox**:
 1. **Create the NAT Network**:
	* Open VirtualBox and go to **File** > **Preferences** > **Network**.
	* Select **NAT Networks**, click **Add** (the green plus sign), and create a new NAT network.
2. **Configure the Network for the Virtual Machines**:
	* For each virtual machine (**malcolm** and **victim**), open the VM settings.
	* Go to the **Network** tab.
	* Under **Attached to**, choose **NAT Network** and select the NAT network you just created.

This configuration will ensure that both machines can communicate with each other while being isolated from the external network.

### Useful Commands
During the project, there were several commands that I used frequently for testing and debugging. Below is a list of useful commands:
* `arp -n` - This command shows the current ARP cache, allowing you to view the mapping of IP addresses to MAC addresses.
* `arp -d 10.0.2.3` - This command deletes the entry for IP address **10.0.2.3** from the ARP cache, which forces the machine to re-query for the MAC address.
* `ping -c 1 10.0.3.1` - This sends a single ping packet to the IP **10.0.3.1**, which helps trigger the ARP request from the victim machine that our program will respond to.
* `tcpdump -i enp0s3 -vvv arp` - This command captures ARP (`icmp` flag for capture ICMP  - Type of package that ping sends) packets on the interface **enp0s3** and provides verbose output, which helps in monitoring the ARP traffic on the victim machine.
* `ifconfig` - This command shows the IP addresses and MAC addresses of all active network interfaces on the machine, helping to gather network information for configuring the program.
* `nmap -sn 192.168.1.0/24 | grep "Nmap scan report for\|MAC Address"` - This command shows IP and MAK of all hosts connected to the same LAN as you.
