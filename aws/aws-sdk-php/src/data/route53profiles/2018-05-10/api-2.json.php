<?php
// This file was auto-generated from sdk-root/src/data/route53profiles/2018-05-10/api-2.json
return [ 'version' => '2.0', 'metadata' => [ 'apiVersion' => '2018-05-10', 'endpointPrefix' => 'route53profiles', 'jsonVersion' => '1.1', 'protocol' => 'rest-json', 'protocols' => [ 'rest-json', ], 'serviceFullName' => 'Route 53 Profiles', 'serviceId' => 'Route53Profiles', 'signatureVersion' => 'v4', 'signingName' => 'route53profiles', 'uid' => 'route53profiles-2018-05-10', ], 'operations' => [ 'AssociateProfile' => [ 'name' => 'AssociateProfile', 'http' => [ 'method' => 'POST', 'requestUri' => '/profileassociation', 'responseCode' => 200, ], 'input' => [ 'shape' => 'AssociateProfileRequest', ], 'output' => [ 'shape' => 'AssociateProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ResourceExistsException', ], [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], ], 'AssociateResourceToProfile' => [ 'name' => 'AssociateResourceToProfile', 'http' => [ 'method' => 'POST', 'requestUri' => '/profileresourceassociation', 'responseCode' => 200, ], 'input' => [ 'shape' => 'AssociateResourceToProfileRequest', ], 'output' => [ 'shape' => 'AssociateResourceToProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InternalServiceErrorException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], ], 'CreateProfile' => [ 'name' => 'CreateProfile', 'http' => [ 'method' => 'POST', 'requestUri' => '/profile', 'responseCode' => 200, ], 'input' => [ 'shape' => 'CreateProfileRequest', ], 'output' => [ 'shape' => 'CreateProfileResponse', ], 'errors' => [ [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], ], 'DeleteProfile' => [ 'name' => 'DeleteProfile', 'http' => [ 'method' => 'DELETE', 'requestUri' => '/profile/{ProfileId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'DeleteProfileRequest', ], 'output' => [ 'shape' => 'DeleteProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], 'idempotent' => true, ], 'DisassociateProfile' => [ 'name' => 'DisassociateProfile', 'http' => [ 'method' => 'DELETE', 'requestUri' => '/profileassociation/Profileid/{ProfileId}/resourceid/{ResourceId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'DisassociateProfileRequest', ], 'output' => [ 'shape' => 'DisassociateProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], 'idempotent' => true, ], 'DisassociateResourceFromProfile' => [ 'name' => 'DisassociateResourceFromProfile', 'http' => [ 'method' => 'DELETE', 'requestUri' => '/profileresourceassociation/profileid/{ProfileId}/resourcearn/{ResourceArn}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'DisassociateResourceFromProfileRequest', ], 'output' => [ 'shape' => 'DisassociateResourceFromProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InternalServiceErrorException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], 'idempotent' => true, ], 'GetProfile' => [ 'name' => 'GetProfile', 'http' => [ 'method' => 'GET', 'requestUri' => '/profile/{ProfileId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'GetProfileRequest', ], 'output' => [ 'shape' => 'GetProfileResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], ], 'GetProfileAssociation' => [ 'name' => 'GetProfileAssociation', 'http' => [ 'method' => 'GET', 'requestUri' => '/profileassociation/{ProfileAssociationId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'GetProfileAssociationRequest', ], 'output' => [ 'shape' => 'GetProfileAssociationResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], ], 'GetProfileResourceAssociation' => [ 'name' => 'GetProfileResourceAssociation', 'http' => [ 'method' => 'GET', 'requestUri' => '/profileresourceassociation/{ProfileResourceAssociationId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'GetProfileResourceAssociationRequest', ], 'output' => [ 'shape' => 'GetProfileResourceAssociationResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], ], 'ListProfileAssociations' => [ 'name' => 'ListProfileAssociations', 'http' => [ 'method' => 'GET', 'requestUri' => '/profileassociations', 'responseCode' => 200, ], 'input' => [ 'shape' => 'ListProfileAssociationsRequest', ], 'output' => [ 'shape' => 'ListProfileAssociationsResponse', ], 'errors' => [ [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'InvalidNextTokenException', ], ], ], 'ListProfileResourceAssociations' => [ 'name' => 'ListProfileResourceAssociations', 'http' => [ 'method' => 'GET', 'requestUri' => '/profileresourceassociations/profileid/{ProfileId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'ListProfileResourceAssociationsRequest', ], 'output' => [ 'shape' => 'ListProfileResourceAssociationsResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'InternalServiceErrorException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'InvalidNextTokenException', ], ], ], 'ListProfiles' => [ 'name' => 'ListProfiles', 'http' => [ 'method' => 'GET', 'requestUri' => '/profiles', 'responseCode' => 200, ], 'input' => [ 'shape' => 'ListProfilesRequest', ], 'output' => [ 'shape' => 'ListProfilesResponse', ], 'errors' => [ [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'InvalidNextTokenException', ], ], ], 'ListTagsForResource' => [ 'name' => 'ListTagsForResource', 'http' => [ 'method' => 'GET', 'requestUri' => '/tags/{ResourceArn}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'ListTagsForResourceRequest', ], 'output' => [ 'shape' => 'ListTagsForResourceResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], ], 'TagResource' => [ 'name' => 'TagResource', 'http' => [ 'method' => 'POST', 'requestUri' => '/tags/{ResourceArn}', 'responseCode' => 204, ], 'input' => [ 'shape' => 'TagResourceRequest', ], 'output' => [ 'shape' => 'TagResourceResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], ], 'idempotent' => true, ], 'UntagResource' => [ 'name' => 'UntagResource', 'http' => [ 'method' => 'DELETE', 'requestUri' => '/tags/{ResourceArn}', 'responseCode' => 204, ], 'input' => [ 'shape' => 'UntagResourceRequest', ], 'output' => [ 'shape' => 'UntagResourceResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], 'idempotent' => true, ], 'UpdateProfileResourceAssociation' => [ 'name' => 'UpdateProfileResourceAssociation', 'http' => [ 'method' => 'PATCH', 'requestUri' => '/profileresourceassociation/{ProfileResourceAssociationId}', 'responseCode' => 200, ], 'input' => [ 'shape' => 'UpdateProfileResourceAssociationRequest', ], 'output' => [ 'shape' => 'UpdateProfileResourceAssociationResponse', ], 'errors' => [ [ 'shape' => 'ResourceNotFoundException', ], [ 'shape' => 'LimitExceededException', ], [ 'shape' => 'InternalServiceErrorException', ], [ 'shape' => 'InvalidParameterException', ], [ 'shape' => 'ThrottlingException', ], [ 'shape' => 'ValidationException', ], [ 'shape' => 'AccessDeniedException', ], [ 'shape' => 'ConflictException', ], ], ], ], 'shapes' => [ 'AccessDeniedException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], 'AccountId' => [ 'type' => 'string', 'max' => 32, 'min' => 12, ], 'Arn' => [ 'type' => 'string', 'max' => 255, 'min' => 1, ], 'AssociateProfileRequest' => [ 'type' => 'structure', 'required' => [ 'Name', 'ProfileId', 'ResourceId', ], 'members' => [ 'Name' => [ 'shape' => 'Name', ], 'ProfileId' => [ 'shape' => 'ResourceId', ], 'ResourceId' => [ 'shape' => 'ResourceId', ], 'Tags' => [ 'shape' => 'TagList', ], ], ], 'AssociateProfileResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileAssociation' => [ 'shape' => 'ProfileAssociation', ], ], ], 'AssociateResourceToProfileRequest' => [ 'type' => 'structure', 'required' => [ 'Name', 'ProfileId', 'ResourceArn', ], 'members' => [ 'Name' => [ 'shape' => 'Name', ], 'ProfileId' => [ 'shape' => 'ResourceId', ], 'ResourceArn' => [ 'shape' => 'Arn', ], 'ResourceProperties' => [ 'shape' => 'ResourceProperties', ], ], ], 'AssociateResourceToProfileResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileResourceAssociation' => [ 'shape' => 'ProfileResourceAssociation', ], ], ], 'ConflictException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], 'CreateProfileRequest' => [ 'type' => 'structure', 'required' => [ 'ClientToken', 'Name', ], 'members' => [ 'ClientToken' => [ 'shape' => 'CreatorRequestId', 'idempotencyToken' => true, ], 'Name' => [ 'shape' => 'Name', ], 'Tags' => [ 'shape' => 'TagList', ], ], ], 'CreateProfileResponse' => [ 'type' => 'structure', 'members' => [ 'Profile' => [ 'shape' => 'Profile', ], ], ], 'CreatorRequestId' => [ 'type' => 'string', 'max' => 255, 'min' => 1, ], 'DeleteProfileRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileId', ], 'members' => [ 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileId', ], ], ], 'DeleteProfileResponse' => [ 'type' => 'structure', 'members' => [ 'Profile' => [ 'shape' => 'Profile', ], ], ], 'DisassociateProfileRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileId', 'ResourceId', ], 'members' => [ 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileId', ], 'ResourceId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ResourceId', ], ], ], 'DisassociateProfileResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileAssociation' => [ 'shape' => 'ProfileAssociation', ], ], ], 'DisassociateResourceFromProfileRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileId', 'ResourceArn', ], 'members' => [ 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileId', ], 'ResourceArn' => [ 'shape' => 'Arn', 'location' => 'uri', 'locationName' => 'ResourceArn', ], ], ], 'DisassociateResourceFromProfileResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileResourceAssociation' => [ 'shape' => 'ProfileResourceAssociation', ], ], ], 'ExceptionMessage' => [ 'type' => 'string', ], 'GetProfileAssociationRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileAssociationId', ], 'members' => [ 'ProfileAssociationId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileAssociationId', ], ], ], 'GetProfileAssociationResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileAssociation' => [ 'shape' => 'ProfileAssociation', ], ], ], 'GetProfileRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileId', ], 'members' => [ 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileId', ], ], ], 'GetProfileResourceAssociationRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileResourceAssociationId', ], 'members' => [ 'ProfileResourceAssociationId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileResourceAssociationId', ], ], ], 'GetProfileResourceAssociationResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileResourceAssociation' => [ 'shape' => 'ProfileResourceAssociation', ], ], ], 'GetProfileResponse' => [ 'type' => 'structure', 'members' => [ 'Profile' => [ 'shape' => 'Profile', ], ], ], 'InternalServiceErrorException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], 'InvalidNextTokenException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'String', ], ], 'exception' => true, ], 'InvalidParameterException' => [ 'type' => 'structure', 'required' => [ 'Message', ], 'members' => [ 'FieldName' => [ 'shape' => 'String', ], 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], 'LimitExceededException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'String', ], 'ResourceType' => [ 'shape' => 'String', ], ], 'exception' => true, ], 'ListProfileAssociationsRequest' => [ 'type' => 'structure', 'members' => [ 'MaxResults' => [ 'shape' => 'MaxResults', 'location' => 'querystring', 'locationName' => 'maxResults', ], 'NextToken' => [ 'shape' => 'NextToken', 'location' => 'querystring', 'locationName' => 'nextToken', ], 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'querystring', 'locationName' => 'profileId', ], 'ResourceId' => [ 'shape' => 'ResourceId', 'location' => 'querystring', 'locationName' => 'resourceId', ], ], ], 'ListProfileAssociationsResponse' => [ 'type' => 'structure', 'members' => [ 'NextToken' => [ 'shape' => 'NextToken', ], 'ProfileAssociations' => [ 'shape' => 'ProfileAssociations', ], ], ], 'ListProfileResourceAssociationsRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileId', ], 'members' => [ 'MaxResults' => [ 'shape' => 'MaxResults', 'location' => 'querystring', 'locationName' => 'maxResults', ], 'NextToken' => [ 'shape' => 'NextToken', 'location' => 'querystring', 'locationName' => 'nextToken', ], 'ProfileId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileId', ], 'ResourceType' => [ 'shape' => 'String', 'location' => 'querystring', 'locationName' => 'resourceType', ], ], ], 'ListProfileResourceAssociationsResponse' => [ 'type' => 'structure', 'members' => [ 'NextToken' => [ 'shape' => 'NextToken', ], 'ProfileResourceAssociations' => [ 'shape' => 'ProfileResourceAssociations', ], ], ], 'ListProfilesRequest' => [ 'type' => 'structure', 'members' => [ 'MaxResults' => [ 'shape' => 'MaxResults', 'location' => 'querystring', 'locationName' => 'maxResults', ], 'NextToken' => [ 'shape' => 'NextToken', 'location' => 'querystring', 'locationName' => 'nextToken', ], ], ], 'ListProfilesResponse' => [ 'type' => 'structure', 'members' => [ 'NextToken' => [ 'shape' => 'NextToken', ], 'ProfileSummaries' => [ 'shape' => 'ProfileSummaryList', ], ], ], 'ListTagsForResourceRequest' => [ 'type' => 'structure', 'required' => [ 'ResourceArn', ], 'members' => [ 'ResourceArn' => [ 'shape' => 'Arn', 'location' => 'uri', 'locationName' => 'ResourceArn', ], ], ], 'ListTagsForResourceResponse' => [ 'type' => 'structure', 'required' => [ 'Tags', ], 'members' => [ 'Tags' => [ 'shape' => 'TagMap', ], ], ], 'MaxResults' => [ 'type' => 'integer', 'box' => true, 'max' => 100, 'min' => 1, ], 'Name' => [ 'type' => 'string', 'max' => 64, 'min' => 0, 'pattern' => '^(?!^[0-9]+$)([a-zA-Z0-9\\-_\' \']+)$', ], 'NextToken' => [ 'type' => 'string', ], 'Profile' => [ 'type' => 'structure', 'members' => [ 'Arn' => [ 'shape' => 'Arn', ], 'ClientToken' => [ 'shape' => 'CreatorRequestId', ], 'CreationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Id' => [ 'shape' => 'ResourceId', ], 'ModificationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Name' => [ 'shape' => 'Name', ], 'OwnerId' => [ 'shape' => 'AccountId', ], 'ShareStatus' => [ 'shape' => 'ShareStatus', ], 'Status' => [ 'shape' => 'ProfileStatus', ], 'StatusMessage' => [ 'shape' => 'String', ], ], ], 'ProfileAssociation' => [ 'type' => 'structure', 'members' => [ 'CreationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Id' => [ 'shape' => 'ResourceId', ], 'ModificationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Name' => [ 'shape' => 'Name', ], 'OwnerId' => [ 'shape' => 'AccountId', ], 'ProfileId' => [ 'shape' => 'ResourceId', ], 'ResourceId' => [ 'shape' => 'ResourceId', ], 'Status' => [ 'shape' => 'ProfileStatus', ], 'StatusMessage' => [ 'shape' => 'String', ], ], ], 'ProfileAssociations' => [ 'type' => 'list', 'member' => [ 'shape' => 'ProfileAssociation', ], ], 'ProfileResourceAssociation' => [ 'type' => 'structure', 'members' => [ 'CreationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Id' => [ 'shape' => 'ResourceId', ], 'ModificationTime' => [ 'shape' => 'Rfc3339Timestamp', ], 'Name' => [ 'shape' => 'Name', ], 'OwnerId' => [ 'shape' => 'AccountId', ], 'ProfileId' => [ 'shape' => 'ResourceId', ], 'ResourceArn' => [ 'shape' => 'Arn', ], 'ResourceProperties' => [ 'shape' => 'ResourceProperties', ], 'ResourceType' => [ 'shape' => 'String', ], 'Status' => [ 'shape' => 'ProfileStatus', ], 'StatusMessage' => [ 'shape' => 'String', ], ], ], 'ProfileResourceAssociations' => [ 'type' => 'list', 'member' => [ 'shape' => 'ProfileResourceAssociation', ], ], 'ProfileStatus' => [ 'type' => 'string', 'enum' => [ 'COMPLETE', 'DELETING', 'UPDATING', 'CREATING', 'DELETED', 'FAILED', ], ], 'ProfileSummary' => [ 'type' => 'structure', 'members' => [ 'Arn' => [ 'shape' => 'Arn', ], 'Id' => [ 'shape' => 'ResourceId', ], 'Name' => [ 'shape' => 'Name', ], 'ShareStatus' => [ 'shape' => 'ShareStatus', ], ], ], 'ProfileSummaryList' => [ 'type' => 'list', 'member' => [ 'shape' => 'ProfileSummary', ], ], 'ResourceExistsException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'String', ], 'ResourceType' => [ 'shape' => 'String', ], ], 'exception' => true, ], 'ResourceId' => [ 'type' => 'string', 'max' => 64, 'min' => 1, ], 'ResourceNotFoundException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'String', ], 'ResourceType' => [ 'shape' => 'String', ], ], 'exception' => true, ], 'ResourceProperties' => [ 'type' => 'string', ], 'Rfc3339Timestamp' => [ 'type' => 'timestamp', ], 'ShareStatus' => [ 'type' => 'string', 'enum' => [ 'NOT_SHARED', 'SHARED_WITH_ME', 'SHARED_BY_ME', ], ], 'String' => [ 'type' => 'string', ], 'Tag' => [ 'type' => 'structure', 'required' => [ 'Key', 'Value', ], 'members' => [ 'Key' => [ 'shape' => 'TagKey', ], 'Value' => [ 'shape' => 'TagValue', ], ], ], 'TagKey' => [ 'type' => 'string', 'max' => 128, 'min' => 1, ], 'TagKeyList' => [ 'type' => 'list', 'member' => [ 'shape' => 'TagKey', ], 'max' => 200, 'min' => 0, ], 'TagList' => [ 'type' => 'list', 'member' => [ 'shape' => 'Tag', ], 'max' => 200, 'min' => 0, ], 'TagMap' => [ 'type' => 'map', 'key' => [ 'shape' => 'TagKey', ], 'value' => [ 'shape' => 'TagValue', ], 'max' => 200, 'min' => 0, ], 'TagResourceRequest' => [ 'type' => 'structure', 'required' => [ 'ResourceArn', 'Tags', ], 'members' => [ 'ResourceArn' => [ 'shape' => 'Arn', 'location' => 'uri', 'locationName' => 'ResourceArn', ], 'Tags' => [ 'shape' => 'TagMap', ], ], ], 'TagResourceResponse' => [ 'type' => 'structure', 'members' => [], ], 'TagValue' => [ 'type' => 'string', 'max' => 256, 'min' => 0, ], 'ThrottlingException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], 'UntagResourceRequest' => [ 'type' => 'structure', 'required' => [ 'ResourceArn', 'TagKeys', ], 'members' => [ 'ResourceArn' => [ 'shape' => 'Arn', 'location' => 'uri', 'locationName' => 'ResourceArn', ], 'TagKeys' => [ 'shape' => 'TagKeyList', 'location' => 'querystring', 'locationName' => 'tagKeys', ], ], ], 'UntagResourceResponse' => [ 'type' => 'structure', 'members' => [], ], 'UpdateProfileResourceAssociationRequest' => [ 'type' => 'structure', 'required' => [ 'ProfileResourceAssociationId', ], 'members' => [ 'Name' => [ 'shape' => 'Name', ], 'ProfileResourceAssociationId' => [ 'shape' => 'ResourceId', 'location' => 'uri', 'locationName' => 'ProfileResourceAssociationId', ], 'ResourceProperties' => [ 'shape' => 'ResourceProperties', ], ], ], 'UpdateProfileResourceAssociationResponse' => [ 'type' => 'structure', 'members' => [ 'ProfileResourceAssociation' => [ 'shape' => 'ProfileResourceAssociation', ], ], ], 'ValidationException' => [ 'type' => 'structure', 'members' => [ 'Message' => [ 'shape' => 'ExceptionMessage', ], ], 'exception' => true, ], ],];