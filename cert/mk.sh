openssl genrsa -out ${clientpath}/${username}.key 1024
openssl req -new -key ${clientpath}/${username}.key -out ${clientpath}/${username}.csr -subj "/C=CN/ST=BeiJing/L=HaiDian/O=legendsec/OU=legendsec/CN=${username}"
openssl x509 -req -days 3650 -CA ${capath}/miniCa.pem  -CAkey ${capath}/miniCa.key -CAcreateserial -in ${clientpath}/${username}.csr -out ${clientpath}/${username}.crt
openssl pkcs12 -export -clcerts -in ${clientpath}/${username}.crt -inkey ${clientpath}/${username}.key -out ${clientpath}/${username}.pfx -password pass:${password}
