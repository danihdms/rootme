#!/usr/bin/env python3
"""
Analyze DirectX Compute Shader on Linux
"""
import struct
import sys
from typing import Dict, List, Tuple, Optional

class DXBCAnalyzer:
    """Analyzer for DirectX Bytecode (DXBC) files"""
    
    def __init__(self, data: bytes):
        self.data = data
        self.chunks = {}
        self.parsed = False
    
    def parse_header(self) -> bool:
        """Parse DXBC header"""
        if len(self.data) < 32:
            print("❌ File too small for DXBC")
            return False
        
        # Check signature
        signature = self.data[:4]
        if signature != b'DXBC':
            print(f"❌ Invalid signature: {signature}")
            return False
        
        print("✓ Valid DXBC file")
        
        # Parse header
        self.checksum = self.data[4:20]
        self.version = struct.unpack('<I', self.data[20:24])[0]
        self.total_size = struct.unpack('<I', self.data[24:28])[0]
        self.chunk_count = struct.unpack('<I', self.data[28:32])[0]
        
        print(f"Version: {self.version}")
        print(f"Total Size: {self.total_size}")
        print(f"Chunk Count: {self.chunk_count}")
        
        return True
    
    def parse_chunks(self):
        """Parse all chunks in the DXBC file"""
        if not self.parse_header():
            return
        
        # Read chunk offsets
        chunk_offsets = []
        for i in range(self.chunk_count):
            offset_pos = 32 + i * 4
            offset = struct.unpack('<I', self.data[offset_pos:offset_pos + 4])[0]
            chunk_offsets.append(offset)
        
        print(f"\nChunk offsets: {[hex(x) for x in chunk_offsets]}")
        
        # Parse each chunk
        for i, offset in enumerate(chunk_offsets):
            chunk_tag = self.data[offset:offset + 4]
            chunk_size = struct.unpack('<I', self.data[offset + 4:offset + 8])[0]
            chunk_data = self.data[offset + 8:offset + 8 + chunk_size]
            
            print(f"\nChunk {i}: {chunk_tag} ({chunk_size} bytes)")
            self.chunks[chunk_tag] = chunk_data
            
            # Analyze specific chunk types
            if chunk_tag == b'SHDR' or chunk_tag == b'SHEX':
                self.analyze_shader_chunk(chunk_data)
            elif chunk_tag == b'RDEF':
                self.analyze_resource_def(chunk_data)
            elif chunk_tag == b'STAT':
                self.analyze_statistics(chunk_data)
    
    def analyze_shader_chunk(self, data: bytes):
        """Analyze shader bytecode chunk"""
        print("  📍 Shader Bytecode Chunk")
        
        if len(data) < 8:
            return
        
        # Shader version and type
        version_token = struct.unpack('<I', data[:4])[0]
        shader_type = (version_token >> 16) & 0xFFFF
        shader_version = version_token & 0xFFFF
        
        type_names = {
            0xFFFF: "Pixel Shader",
            0xFFFE: "Vertex Shader", 
            0x4353: "Compute Shader",
            0x4753: "Geometry Shader",
            0x4853: "Hull Shader",
            0x4453: "Domain Shader"
        }
        
        type_name = type_names.get(shader_type, f"Unknown (0x{shader_type:04x})")
        major_ver = (shader_version >> 8) & 0xFF
        minor_ver = shader_version & 0xFF
        
        print(f"  Type: {type_name}")
        print(f"  Version: {major_ver}.{minor_ver}")
        
        # Try to extract some instructions
        self.disassemble_instructions(data[4:])
    
    def disassemble_instructions(self, data: bytes):
        """Basic disassembly of shader instructions"""
        print("  📍 Shader Instructions (partial):")
        
        pos = 0
        instruction_count = 0
        
        while pos < len(data) - 4 and instruction_count < 20:  # Limit output
            try:
                # Read instruction token
                token = struct.unpack('<I', data[pos:pos + 4])[0]
                opcode = token & 0x7FF
                length = (token >> 24) & 0x7F
                
                if length == 0:
                    break
                
                # Get instruction data
                instr_data = data[pos:pos + length * 4]
                
                # Basic opcode mapping (incomplete)
                opcodes = {
                    0: "add", 1: "and", 2: "break", 3: "breakc", 4: "call",
                    5: "callc", 6: "case", 7: "continue", 8: "continuec",
                    9: "cut", 10: "default", 11: "deriv_rtx", 12: "deriv_rty",
                    13: "discard", 14: "div", 15: "dp2", 16: "dp3", 17: "dp4",
                    18: "else", 19: "emit", 20: "emitthencut", 21: "endif",
                    22: "endloop", 23: "endswitch", 24: "eq", 25: "exp",
                    26: "frc", 27: "ftoi", 28: "ftou", 29: "ge", 30: "iadd",
                    31: "if", 32: "ige", 33: "ilt", 34: "imad", 35: "imax",
                    36: "imin", 37: "imul", 38: "ine", 39: "ineg", 40: "ishl",
                    41: "ishr", 42: "itof", 43: "label", 44: "ld", 45: "ld_ms",
                    46: "log", 47: "loop", 48: "lt", 49: "mad", 50: "min",
                    51: "max", 52: "customdata", 53: "mov", 54: "movc",
                    55: "mul", 56: "ne", 57: "nop", 58: "not", 59: "or",
                    60: "resinfo", 61: "ret", 62: "retc", 63: "round_ne",
                    64: "round_ni", 65: "round_pi", 66: "round_z", 67: "rsq",
                    68: "sample", 69: "sample_c", 70: "sample_c_lz",
                    71: "sample_l", 72: "sample_d", 73: "sample_b", 74: "sqrt",
                    75: "switch", 76: "sincos", 77: "udiv", 78: "ult",
                    79: "uge", 80: "umul", 81: "umad", 82: "umax", 83: "umin",
                    84: "ushr", 85: "utof", 86: "xor", 139: "ld_raw",
                    140: "store_raw", 141: "ld_structured", 142: "store_structured",
                    143: "atomic_and", 144: "atomic_or", 145: "atomic_xor",
                    146: "atomic_cmp_store", 147: "atomic_iadd", 148: "atomic_imax",
                    149: "atomic_imin", 150: "atomic_umax", 151: "atomic_umin"
                }
                
                opcode_name = opcodes.get(opcode, f"unk_{opcode}")
                
                print(f"    {pos:04x}: {opcode_name} (len={length})")
                
                pos += length * 4
                instruction_count += 1
                
            except:
                break
        
        if instruction_count >= 20:
            print("    ... (truncated)")
    
    def analyze_resource_def(self, data: bytes):
        """Analyze resource definition chunk"""
        print("  📍 Resource Definition Chunk")
        # This would contain constant buffer layouts, etc.
        if len(data) >= 4:
            cb_count = struct.unpack('<I', data[:4])[0]
            print(f"  Constant Buffers: {cb_count}")
    
    def analyze_statistics(self, data: bytes):
        """Analyze statistics chunk"""
        print("  📍 Statistics Chunk")
        if len(data) >= 32:
            stats = struct.unpack('<8I', data[:32])
            print(f"  Instructions: {stats[0]}")
            print(f"  Temp registers: {stats[1]}")
            print(f"  Def count: {stats[2]}")
    
    def extract_raw_bytecode(self) -> Optional[bytes]:
        """Extract raw shader bytecode for further analysis"""
        if b'SHDR' in self.chunks:
            return self.chunks[b'SHDR']
        elif b'SHEX' in self.chunks:
            return self.chunks[b'SHEX']
        return None

def analyze_shader_file(filepath: str):
    """Main function to analyze a shader file"""
    try:
        with open(filepath, 'rb') as f:
            data = f.read()
        
        print(f"📁 Analyzing: {filepath}")
        print(f"📏 File size: {len(data)} bytes")
        print("=" * 50)
        
        analyzer = DXBCAnalyzer(data)
        analyzer.parse_chunks()
        
        # Extract raw bytecode for hex dump
        raw_bytecode = analyzer.extract_raw_bytecode()
        if raw_bytecode:
            print("\n" + "=" * 50)
            print("🔍 Raw Shader Bytecode (first 256 bytes):")
            hex_dump(raw_bytecode[:256])
        
        return analyzer
        
    except FileNotFoundError:
        print(f"❌ File not found: {filepath}")
    except Exception as e:
        print(f"❌ Error analyzing file: {e}")
    
    return None

def hex_dump(data: bytes, width: int = 16):
    """Create a hex dump of binary data"""
    for i in range(0, len(data), width):
        chunk = data[i:i + width]
        hex_part = ' '.join(f'{b:02x}' for b in chunk)
        ascii_part = ''.join(chr(b) if 32 <= b <= 126 else '.' for b in chunk)
        print(f"{i:04x}: {hex_part:<48} {ascii_part}")

def main():
    if len(sys.argv) != 2:
        print("Usage: python shader_analyzer.py <shader_file>")
        print("Example: python shader_analyzer.py shader_resource_101.bin")
        sys.exit(1)
    
    shader_file = sys.argv[1]
    analyzer = analyze_shader_file(shader_file)
    
    if analyzer:
        print("\n" + "=" * 50)
        print("📋 Summary:")
        print("- This is a DirectX Compute Shader")
        print("- It's used for GPU-accelerated decryption")
        print("- The algorithm is in the shader instructions above")
        print("\n🔄 Next steps:")
        print("1. Study the disassembled instructions")
        print("2. Look for XOR, ADD, ROL/ROR operations")
        print("3. Identify the key scheduling/usage pattern")
        print("4. Implement the reverse algorithm in Python")

if __name__ == "__main__":
    main()
