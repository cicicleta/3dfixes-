import re

with open('shaderUsage.xml', 'r', encoding='utf-8') as f:
    content = f.read()

pattern = r'<PixelShader hash="([^"]+)">.*?</PixelShader>'
results = []

for match in re.finditer(pattern, content, re.DOTALL):
    ps_hash = match.group(1)
    ps_block = match.group(0)
    
    # Extrae TODOS los DepthTarget hashes
    depth_targets = re.findall(r'<DepthTarget\s+handle=[^>]*>([^<]+)</DepthTarget>', ps_block)
    
    # Extrae Register con id y hash
    registers = re.findall(r'<Register\s+id=(\d+)\s+handle=[^>]*>([^<]+)</Register>', ps_block)
    
    # Busca si c5057d7e está en DepthTarget
    if 'c5057d7e' in depth_targets:
        # Busca el id (slot) donde está c5057d7e en Register
        for slot_id, reg_hash in registers:
            if reg_hash == 'c5057d7e':
                results.append((ps_hash, slot_id))
                break  # Solo el primer match

# Generar .ini
with open('depth_overrides.ini', 'w') as f:
    for ps_hash, slot in results:
        f.write(f'[ShaderOverride_{ps_hash}]\n')
        f.write(f'hash = {ps_hash}\n')
        f.write(f'ResourceDepthBuffer = ps-t{slot}\n')
        f.write(f'\n')

print(f"Generados {len(results)} overrides")
print("Guardados en: depth_overrides.ini")