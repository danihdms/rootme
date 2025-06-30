#!/usr/bin/env python3
"""
CTF Challenge Solver - Decrypt the payload without waiting 10 minutes per chunk
"""
import requests
import struct
from typing import List, Optional

# Server details from the decompiled code
SERVER = "57.128.85.25:50002"
BASE_URL = f"http://{SERVER}"

def get_payload_size() -> Optional[int]:
    """Get the total payload size from the server"""
    try:
        response = requests.get(f"{BASE_URL}/size", timeout=10)
        if response.status_code == 200:
            size = int(response.text.strip())
            print(f"Payload size: {size} bytes")
            return size
    except Exception as e:
        print(f"Error getting payload size: {e}")
    return None

def download_chunk(chunk_index: int) -> Optional[bytes]:
    """Download a specific chunk from the server"""
    try:
        # The decompiled code shows: chunk_id = chunk_index + 1
        chunk_id = chunk_index + 1
        url = f"{BASE_URL}/{chunk_id}"  # Based on the format string in sub_1400018B1
        
        print(f"Downloading chunk {chunk_index} from {url}")
        response = requests.get(url, timeout=10)
        
        if response.status_code == 200:
            chunk_data = response.content[:16]  # Each chunk is 16 bytes max
            print(f"Downloaded chunk {chunk_index}: {len(chunk_data)} bytes")
            return chunk_data
        else:
            print(f"Failed to download chunk {chunk_index}: HTTP {response.status_code}")
    except Exception as e:
        print(f"Error downloading chunk {chunk_index}: {e}")
    return None

def decrypt_chunk(chunk_data: bytes, chunk_index: int) -> bytes:
    """
    Decrypt a chunk using the algorithm from sub_140001872
    key = -559038737 - 66 * chunk_index
    
    Note: This is a placeholder - you need to implement the actual
    decryption algorithm from the compute shader!
    """
    key = (-559038737 - 66 * chunk_index) & 0xFFFFFFFF  # Keep as 32-bit
    
    # TODO: Implement the actual decryption algorithm
    # You need to reverse the compute shader to understand the algorithm
    
    print(f"Decrypting chunk {chunk_index} with key 0x{key:08x}")
    
    # Placeholder XOR decryption (probably not correct)
    decrypted = bytearray()
    key_bytes = struct.pack('<I', key)  # Little-endian 32-bit
    
    for i, byte in enumerate(chunk_data):
        decrypted.append(byte ^ key_bytes[i % 4])
    
    return bytes(decrypted)

def download_and_decrypt_payload() -> Optional[bytes]:
    """Download and decrypt the complete payload"""
    
    # Get total size
    total_size = get_payload_size()
    if not total_size:
        return None
    
    # Calculate number of chunks (each chunk is 16 bytes)
    num_chunks = (total_size + 15) // 16
    print(f"Need to download {num_chunks} chunks")
    
    decrypted_payload = bytearray()
    
    # Download and decrypt each chunk
    for chunk_index in range(num_chunks):
        chunk_data = download_chunk(chunk_index)
        if not chunk_data:
            print(f"Failed to download chunk {chunk_index}")
            return None
        
        # Decrypt the chunk
        decrypted_chunk = decrypt_chunk(chunk_data, chunk_index)
        
        # Handle the last chunk (might be shorter than 16 bytes)
        if chunk_index == num_chunks - 1:
            remaining = total_size % 16
            if remaining > 0:
                decrypted_chunk = decrypted_chunk[:remaining]
        
        decrypted_payload.extend(decrypted_chunk)
        
        print(f"Progress: {len(decrypted_payload)}/{total_size} bytes")
    
    return bytes(decrypted_payload)

def analyze_payload(payload: bytes):
    """Analyze the decrypted payload"""
    print(f"\nPayload Analysis:")
    print(f"Size: {len(payload)} bytes")
    print(f"First 32 bytes: {payload[:32].hex()}")
    
    # Check for common executable signatures
    if payload.startswith(b'MZ'):
        print("✓ Looks like a PE executable")
    elif payload.startswith(b'\x7fELF'):
        print("✓ Looks like an ELF executable")
    elif payload.startswith(b'\xfc\x48\x83\xe4\xf0'):
        print("✓ Might be shellcode (common prologue)")
    else:
        print("? Unknown format - might need different decryption")

def main():
    print("=== CTF Challenge Solver ===")
    print("Downloading and decrypting payload without 10-minute delays...\n")
    
    # Download and decrypt
    payload = download_and_decrypt_payload()
    
    if payload:
        # Save to file
        with open("decrypted_payload.bin", "wb") as f:
            f.write(payload)
        print(f"\n✓ Saved decrypted payload to decrypted_payload.bin")
        
        # Analyze the payload
        analyze_payload(payload)
        
        print("\n" + "="*50)
        print("IMPORTANT: The decryption algorithm is likely wrong!")
        print("You need to:")
        print("1. Disassemble the compute shader: dxc.exe -dumpbin shader_resource_101.bin")
        print("2. Understand the actual decryption algorithm")
        print("3. Update the decrypt_chunk() function")
        print("4. Re-run this script with the correct algorithm")
    else:
        print("❌ Failed to download/decrypt payload")

if __name__ == "__main__":
    main()
