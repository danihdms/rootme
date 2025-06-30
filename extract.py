#!/usr/bin/env python3
"""
Extract resource ID 101 (compute shader) from the PE file
"""

import pefile
import sys

def extract_resource(pe_path, resource_id=101, resource_type=10):
    """
    Extract a specific resource from PE file
    resource_type 10 = RT_RCDATA
    """
    try:
        pe = pefile.PE(pe_path)
        
        # Check if the PE has resources
        if not hasattr(pe, 'DIRECTORY_ENTRY_RESOURCE'):
            print("No resources found in the PE file")
            return None
        
        # Navigate through resource directory
        for resource_type_entry in pe.DIRECTORY_ENTRY_RESOURCE.entries:
            if resource_type_entry.id == resource_type:  # RT_RCDATA = 10
                print(f"Found resource type {resource_type}")
                
                for resource_id_entry in resource_type_entry.directory.entries:
                    if resource_id_entry.id == resource_id:
                        print(f"Found resource ID {resource_id}")
                        
                        # Get the actual resource data
                        for resource_lang_entry in resource_id_entry.directory.entries:
                            data_rva = resource_lang_entry.data.struct.OffsetToData
                            size = resource_lang_entry.data.struct.Size
                            data = pe.get_memory_mapped_image()[data_rva:data_rva + size]
                            
                            print(f"Resource size: {size} bytes")
                            return data
        
        print(f"Resource ID {resource_id} not found")
        return None
        
    except Exception as e:
        print(f"Error: {e}")
        return None

def analyze_dxbc_header(data):
    """Analyze DXBC (DirectX Bytecode) header"""
    if len(data) < 32:
        print("Data too short to be DXBC")
        return
    
    # DXBC files start with "DXBC" signature
    signature = data[:4]
    print(f"Signature: {signature}")
    
    if signature == b'DXBC':
        print("✓ Valid DXBC (DirectX Bytecode) file")
        # Parse more header info
        checksum = data[4:20].hex()
        version = int.from_bytes(data[20:24], 'little')
        size = int.from_bytes(data[24:28], 'little')
        chunk_count = int.from_bytes(data[28:32], 'little')
        
        print(f"Checksum: {checksum}")
        print(f"Version: {version}")
        print(f"Total Size: {size}")
        print(f"Chunk Count: {chunk_count}")
    else:
        print("⚠ Not a standard DXBC file")
        print(f"First 32 bytes: {data[:32].hex()}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python extract_resource.py <path_to_exe>")
        sys.exit(1)
    
    pe_path = sys.argv[1]
    
    # Extract resource 101
    shader_data = extract_resource(pe_path, resource_id=101, resource_type=10)
    
    if shader_data:
        # Save to file
        with open("shader_resource_101.bin", "wb") as f:
            f.write(shader_data)
        print("✓ Saved to shader_resource_101.bin")
        
        # Analyze the data
        analyze_dxbc_header(shader_data)
        
        print("\n" + "="*50)
        print("Next steps:")
        print("1. Use 'dxc.exe -dumpbin shader_resource_101.bin' to disassemble")
        print("2. Or use online DXBC disassemblers")
        print("3. Reverse the compute shader algorithm")
        print("4. Implement the decryption in your script")
    else:
        print("❌ Failed to extract resource")
