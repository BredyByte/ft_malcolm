# ft_malcolm

> This repository contains a "ft_malcolm" project that is part of the École 42 curriculum.

## Overview
ft_malcolm is a 42 École outer core project focused on networking and cybersecurity. The goal is to develop a program in C that performs MAC address spoofing, allowing manipulation of a victim's network traffic by impersonating critical network devices, such as the gateway, within the local network (LAN).

This project provides hands-on experience with Layer 2 (Data Link Layer) of the OSI model and introduces key networking concepts such as: *Host, Node, Packet, Protocol, IP, MAC, LAN, and ARP*. By working on ft_malcolm, students gain practical knowledge of network packet manipulation, enabling them to understand the inner workings of network communication and security.

## RFC 826 and RFC 7042

To enhance understanding and provide a solid theoretical foundation for ft_malcolm, it's essential to explore relevant RFCs (Request for Comments). RFCs are technical documents and standards published by the Internet Engineering Task Force (IETF) to define protocols and technologies foundational to the internet. For instance, RFC 1918 defines private IP address ranges, while RFC 2616 outlines the HTTP/1.1 protocol used for web communication.

### What is RFC 826?

**RFC 826**, titled *Address Resolution Protocol (ARP)*, defines the protocol used to map IP addresses to MAC addresses within a local area network (LAN). ARP is essential for communication between devices on the same network, as it allows the system to resolve an IP address into a physical MAC address. Without ARP, devices in a LAN wouldn’t be able to discover or communicate with each other efficiently.

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
