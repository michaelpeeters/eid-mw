#ifndef EID_VWR_VERIFY_H
#define EID_VWR_VERIFY_H

/**
  * \defgroup C_API_OSSL OpenSSL-based helper functions
  *
  * These functions are available on GNU/Linux and OS X *only*.
  * @{
  */

/**
  * \file verify_cert.h
  * \brief Helper functions to deal with certificate validation using OpenSSL. Linux/OSX only.
  */

#ifdef __cplusplus
extern "C"
{
#endif

#include <eid-viewer/oslayer.h>

/**
  * \brief Verify the validity of a leaf certificate.
  *
  * This function will verify the validity of a leaf certificate by
  * checking signatures, ensuring they're signed by a valid root
  * certificate, and performing an OCSP request against the OCSP server.
  *
  * \param certificate the X.509 certificate to check, in DER format.
  * \param certlen the length (in bytes) of certificate.
  * \param ca the CA certificate by which the certificate is signed
  * \param calen the length (in bytes) of ca
  * \param perform_ocsp_request a pointer to a function which should
  * perform an HTTP POST request and return the reply. It should return
  * the data as returned by the OCSP server. Its parameters are:
  *   - the URL for the OCSP server
  *   - the data that should be sent (by way of an HTTP POST request) to
  *   the OCSP server
  *   - the length of the above data
  *   - a pointer to store the length of the returned body
  *   - a pointer to store a handle to the request (which may, but is
  *     not required to, be the same as as the return value).
  *  
  * \param free_ocsp_request: called when the return value of
  * perform_ocsp_request is no longer needed. Its parameter will be
  * the data which was returned in perform_ocsp_request's last
  * parameter.
  */
	DllExport enum eid_vwr_result eid_vwr_verify_cert(const void
							  *certificate,
							  size_t certlen,
							  const void *ca,
							  size_t calen,
							  const void
							  *
							  (*perform_ocsp_request)
							  (char *, void *,
							   long, long *,
							   void **),
							  void
							  (*free_ocsp_request)
							  (void *));
/**
  * \brief Verify the validity of an intermediate certificate.
  *
  * This function will verify the validity of an intermediate
  * certificate by checking signatures, ensuring they're signed by a
  * valid root certificate, and performing a CRL check against the
  * correct CRL.
  *
  * \param certificate the X.509 certificate to check, in DER format.
  * \param certlen the length (in bytes) of certificate.
  * \param root the root certificate by which the certificate is signed
  * \param rootlen the length (in bytes) of root.
  * \param perform_http_request a pointer to a function which should
  * perform an HTTP GET request and return the reply. It should return
  * the data as returned by the webserver in question. Its parameters
  * are:
  *  - The URL of the resource to retrieve
  *  - A pointer to store the length of the returned body
  *  - A pointer to store a handle to the request (which may, but is not
  *    required to, be the same as the return value).
  * \param free_http_request: called when the return value of
  * perform_http_request is no longer needed. Its parameter will be the
  * data which was returned in perform_http_request's last parameter.
  */
	DllExport enum eid_vwr_result eid_vwr_verify_int_cert(const void
							  *certificate,
							  size_t certlen,
							  const void *root,
							  size_t rootlen,
							  const void
							  *(*perform_http_request)
							  (char *, long *,
							  void **), void
							  (free_http_request)
							  (void*));

/**
  * \brief Verify the validity of the RRN certificate.
  *
  * This function will verify the validity of the RRN certificate by
  * checking that the certificate is signed by a valid root certificate.
  *
  * \note This function will *not* perform an OCSP request, since the
  * root CA does not have an OCSP server.
  *
  * \param certificate the X.509 certificate to check, in DER format.
  * \param certlen the length (in bytes) of certificate.
  */
	DllExport enum eid_vwr_result eid_vwr_verify_rrncert(const void
							     *certificate,
							     size_t certlen,
							     const void
							     *root_cert,
							     size_t rootlen);
/**
  * \brief Verify the validity of the root certificate
  *
  * This function will verify the validity of the root certificate by
  * checking if the certificate can be found in the trust store.
  *
  * \param certificate the X.509 certificate to check, in DER format
  * \param certlen the length (in bytes) of certificate.
  * \since v5.0
  */
	DllExport enum eid_vwr_result eid_vwr_verify_root_cert(const void *certificate, size_t certlen);
/**
  * \brief Produce a human-readable version of the certificate.
  *
  * This function will call OpenSSL's X509_print_ex() function on the
  * given certificate which produces the output as produced by the
  * command-line call "openssl x509 -in <certificate> -text".
  *
  * \param certificate the certificate for which to get details
  * \param certlen the length of certificate
  *
  * \return a text representation of the certificate. Should be free()d
  * when no longer required.
  */
	DllExport char *eid_vwr_x509_get_details(const void *certificate,
						 size_t certlen);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
