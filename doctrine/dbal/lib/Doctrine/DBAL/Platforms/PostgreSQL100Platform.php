<?php
/*
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This software consists of voluntary contributions made by many individuals
 * and is licensed under the MIT license. For more information, see
 * <http://www.doctrine-project.org>.
 */

namespace Doctrine\DBAL\Platforms;

/**
 * Provides the behavior, features and SQL dialect of the PostgreSQL 10.0 database platform.
 *
 * @link   www.doctrine-project.org
 * @since  2.6
 */
class PostgreSQL100Platform extends PostgreSQL92Platform
{
	/**
	 * {@inheritdoc}
	 */
	protected function getReservedKeywordsClass()
	{
		return Keywords\PostgreSQL100Keywords::class;
	}

	public function getSequenceDataSQL($rawSequenceName, $schemaName)
	{
		$sequenceName = $this->cleanSequenceNameFromSchemaName($rawSequenceName, $schemaName);

		return 'SELECT min_value, increment_by FROM pg_sequences WHERE schemaname = '.$this->quoteStringLiteral($schemaName).' AND sequencename = ' . $this->quoteStringLiteral($sequenceName);
	}

	private function cleanSequenceNameFromSchemaName($rawSequenceName, $schemaName)
	{
		return str_replace($schemaName . '.', '', $rawSequenceName);
	}
}
